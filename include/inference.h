#pragma once
#include "cube.h"

/**
 * @file inference.h
 * @brief Cube state inference tooling
 *
 * This contains the implementation of an algorithm to enable the accurate
 * inference of a Rubik's Cube's state.
 */

using namespace rubiktrace;

std::vector<Layer> deduce_transition_moves(Cube cube, const CubeState& updated_state);
