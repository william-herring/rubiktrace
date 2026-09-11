#include "inference.h"
#include "util.cpp"

using namespace rubiktrace;

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

    // We need to consider any potential hidden prefix moves (i.e. move(s) happened prior but there was no visible state change)
    // These moves could have happened on any of the F, U, D, L, R, B (if face was symmetric) layers
    if (is_face_symmetric(initial_face)) {
        // How many combinations of hidden moves do we actually need to check?
    }

    return result;
}