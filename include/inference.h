#pragma once
#include "cube.h"
#include <set>

/**
 * @file inference.h
 * @brief Cube state inference tooling
 *
 * This contains the implementation of an algorithm to enable the accurate
 * inference of a Rubik's Cube's state.
 */

namespace rubiktrace {
    std::vector<Move> find_hidden_moves(const CubeState& initial_state, const std::vector<Sticker>& current_face);
    std::vector<std::vector<Move>> deduce_possible_transition_sequences(Cube cube, const std::vector<Sticker>& face);
}
