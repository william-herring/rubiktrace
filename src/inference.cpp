#include "inference.h"
#include "../include/util.h"
#include <unordered_set>

using namespace rubiktrace;

namespace {
    // Hidden moves are bounded because the closure could otherwise wander
    constexpr int MAX_HIDDEN_MOVES = 4;

    const std::vector<Move>& all_moves() {
        static const std::vector<Move> moves = [] {
            std::vector<Move> m;
            for (Layer l : {U, F, R, L, B, D}) {
                m.push_back(Move{l, false, 1});
                m.push_back(Move{l, true, 1});
                m.push_back(Move{l, false, 2});
            }
            return m;
        }();
        return moves;
    }

    std::string state_key(const CubeState& s) {
        std::string key;
        // 9*6 = 54 stickers
        key.reserve(54);
        for (const Face* f : {&s.u_face, &s.f_face, &s.r_face, &s.l_face, &s.b_face, &s.d_face})
            for (const Sticker st : *f) key.push_back(static_cast<char>('0' + st));
        return key;
    }

    CubeState after(const CubeState& s, const Move& m) {
        Cube c(s);
        c.do_move(m);
        return c.get_state();
    }
}

std::vector<HiddenPrefix> rubiktrace::hidden_closure(const CubeState& start) {
    std::vector<HiddenPrefix> result{{start, {}}};
    std::unordered_set<std::string> seen{state_key(start)};

    size_t begin = 0;
    for (int depth = 0; depth < MAX_HIDDEN_MOVES; ++depth) {
        const size_t end = result.size();
        for (size_t i = begin; i < end; ++i) {
            for (const Move& m : all_moves()) {
                CubeState next = after(result[i].state, m);
                if (next.f_face != start.f_face) continue; // not hidden
                if (!seen.insert(state_key(next)).second) continue;
                Algorithm path = result[i].moves;
                path.push_back(m);
                result.push_back({std::move(next), std::move(path)});
            }
        }
        begin = end;
    }
    return result;
}

std::vector<CandidateState> rubiktrace::find_candidate_children(CandidateState& parent, const Face& observed_face) {
    std::vector<CandidateState> children;
    std::unordered_set<std::string> seen;

    for (const HiddenPrefix& prefix : hidden_closure(parent.cube_state)) {
        for (const Move& m : all_moves()) {
            CubeState next = after(prefix.state, m);
            if (next.f_face != observed_face) continue;
            if (!seen.insert(state_key(next)).second) continue;

            CandidateState child;
            child.parent = &parent;
            child.cube_state = std::move(next);
            child.transition_from_origin = parent.transition_from_origin;
            child.transition_from_origin.insert(child.transition_from_origin.end(),
                                                prefix.moves.begin(), prefix.moves.end());
            child.transition_from_origin.push_back(m);
            children.push_back(std::move(child));
        }
    }
    return children;
}

std::optional<Algorithm> rubiktrace::completes_to_solved(const CandidateState& candidate) {
    const CubeState solved = Cube().get_state();
    for (const HiddenPrefix& prefix : hidden_closure(candidate.cube_state)) {
        if (prefix.state == solved) {
            Algorithm full = candidate.transition_from_origin;
            full.insert(full.end(), prefix.moves.begin(), prefix.moves.end());
            return full;
        }
    }
    return std::nullopt;
}

std::vector<CandidateState> infer(const CubeState& start, const std::vector<Face>& observed) {
    std::vector<std::deque<CandidateState>> generations(observed.size() + 1);
    generations[0].push_back(CandidateState{nullptr, start, {}});

    for (size_t n = 0; n < observed.size(); ++n) {
        for (CandidateState& parent : generations[n])
            for (CandidateState& child : find_candidate_children(parent, observed[n]))
                generations[n + 1].push_back(std::move(child));
    }

    std::vector<CandidateState> solutions;
    for (const CandidateState& c : generations.back())
        if (auto full = completes_to_solved(c)) {
            CandidateState s = c;
            s.transition_from_origin = *full;
            solutions.push_back(std::move(s));
        }
    return solutions;
}