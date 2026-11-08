#pragma once
#include "cube.h"
#include <set>

/**
 * @file inference.h
 * @brief Cube state inference tooling
 *
 * This contains the implementation of an algorithm to facilitate the accurate
 * inference of a Rubik's Cube's state transitions when supplied with a sequence of single-face state changes.
 */

namespace rubiktrace {
    using Algorithm = std::vector<Move>;

    struct CandidateState {
        CandidateState* parent = nullptr;
        CubeState cube_state;
        Algorithm transition_from_origin;
    };

    struct HiddenPrefix {
        CubeState state;
        Algorithm moves;
    };

    std::vector<HiddenPrefix> hidden_closure(const CubeState& start);

    std::vector<CandidateState> find_candidate_children(CandidateState& parent, const Face& observed_face);

    std::optional<Algorithm> completes_to_solved(const CandidateState& candidate);

    std::vector<CandidateState> infer(const CubeState& start, const std::vector<Face>& observed);
}
