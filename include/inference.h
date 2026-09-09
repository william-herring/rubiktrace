#pragma once
#include "cube.h"

/**
 * @file inference.h
 * @brief Cube state inference tooling
 *
 * This contains the implementation of an algorithm to enable the accurate
 * inference of a Rubik's Cube's state.
 */

namespace rubiktrace {
    std::vector<std::vector<Move>> deduce_possible_transition_sequences(Cube cube, const std::vector<Sticker>& face);
}
