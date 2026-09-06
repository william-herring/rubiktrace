//
// Created by William on 6/9/2026.
//

#include "../include/cube.h"

using namespace rubiktrace;

constexpr std::optional<Move> string_to_move(const std::string& str) {
    if (str == "U") return Move::U;
    if (str == "F") return Move::F;
    if (str == "R") return Move::R;
    if (str == "L") return Move::L;
    if (str == "B") return Move::B;
    if (str == "D") return Move::D;
    return std::nullopt;
}

Cube::Cube() : distance_from_origin(0) {}

Cube::Cube(const std::string& scramble) : distance_from_origin(0) {
    this->state = CubeState();
    this->set_solved();

    std::istringstream scramble_stream(scramble);
    std::string move_sub;
    while (scramble_stream >> move_sub) {
        bool do_inverse = false;
        int repeat = 1;
        if (char move_suffix = move_sub.back(); move_suffix == '\'') {
            do_inverse = true;
        } else if (move_suffix == '2') {
            repeat = 2;
        }
        Move move = string_to_move(move_sub).value();
        this->do_move(move, do_inverse, repeat);
    }
}

void Cube::set_solved() {
    this->state.u_face = std::vector<Face>(9, Face::UP);
    this->state.f_face = std::vector<Face>(9, Face::FRONT);
    this->state.r_face = std::vector<Face>(9, Face::RIGHT);
    this->state.l_face = std::vector<Face>(9, Face::LEFT);
    this->state.b_face = std::vector<Face>(9, Face::BACK);
    this->state.d_face = std::vector<Face>(9, Face::DOWN);
}

void Cube::set_state(const CubeState& new_state) { this->state = new_state; }
CubeState Cube::get_state() const { return this->state; }

void Cube::do_move(Move move, bool do_inverse, int repeat) {
    for (int i = 0; i < repeat; i++) {
        // U move
        // U and D faces are unchanged
        // TODO: State transitions
        switch (move) {
            case Move::U:
                std::vector<Face> l_face = this->state.l_face;
        }

        if (do_inverse) {

        }
    }
}