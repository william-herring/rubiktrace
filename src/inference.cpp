#include "inference.h"
#include "util.cpp"

using namespace rubiktrace;

std::vector<Move> find_hidden_moves(const CubeState& initial_state, const std::vector<Sticker>& current_face) {
    // F moves are always potentially hidden
    std::vector<Move> result = {
        Move{F, false, 1},
        Move{F, true, 1},
        Move{F, false, 2},
    };

    if (is_face_symmetric(initial_state.b_face)) {
        result.push_back(Move{B, false, 1});
        result.push_back(Move{B, true, 1});
        result.push_back(Move{B, false, 2});
    }

    // Test R, L, U, D layers independently out of laziness for now
    Cube test_cube(initial_state);
    std::vector<Layer> layers_to_test = { R, L, U, D };
    for (const auto layer : layers_to_test) {
        std::vector<Move> moves_to_test = {
            Move{layer, false, 1},
            Move{layer, true, 1},
            Move{layer, false, 2},
        };
        for (auto move : moves_to_test) {
            test_cube.do_move(move);
            if (test_cube.get_state().b_face == initial_state.b_face) result.push_back(move);
            test_cube.set_state(initial_state);
        }
    }

    return result;
}

std::vector<std::vector<Move>> deduce_possible_transition_sequences(Cube cube, const std::vector<Sticker>& face) {
    std::vector<std::vector<Move>> result;
    std::set<Layer> potential_terminal_layers;

    // The assumption is that we see the B face
    CubeState initial_state = cube.get_state();
    std::vector<Sticker>& initial_face = initial_state.b_face;

    // Look for edge diff
    if (face[1] != initial_face[1]) potential_terminal_layers.insert(Layer::D);
    else if (face[3] != initial_face[3]) potential_terminal_layers.insert(Layer::L);
    else if (face[5] != initial_face[5]) potential_terminal_layers.insert(Layer::R);
    else if (face[7] != initial_face[7]) potential_terminal_layers.insert(Layer::U);
    // Look for corner diff if edges have not changed
    if (potential_terminal_layers.size() == 0) {
        if (face[0] != initial_face[0]) {
            potential_terminal_layers.insert(Layer::D);
            potential_terminal_layers.insert(Layer::L);
        }
        if (face[2] != initial_face[2]) {
            potential_terminal_layers.insert(Layer::D);
            potential_terminal_layers.insert(Layer::R);
        }
        if (face[6] != initial_face[6]) {
            potential_terminal_layers.insert(Layer::U);
            potential_terminal_layers.insert(Layer::L);
        }
        if (face[8] != initial_face[8]) {
            potential_terminal_layers.insert(Layer::U);
            potential_terminal_layers.insert(Layer::R);
        }
    }



    return result;
}