#include "inference.h"
#include "util.cpp"

using namespace rubiktrace;

std::vector<std::vector<Move>> deduce_possible_transition_sequences(Cube cube, const std::vector<Sticker>& face) {
    std::vector<std::vector<Move>> result;

    // The assumption is that we see the B face
    CubeState initial_state = cube.get_state();
    std::vector<Sticker>& initial_face = initial_state.b_face;

    // We need to consider any potential hidden prefix moves (i.e. move(s) happened prior but there was no visible state change)
    // These moves could have happened on any of the F, U, D, L, R, B (if face was symmetric) layers
    if (is_face_symmetric(initial_face)) {
        // How many combinations of hidden moves do we actually need to check?
    }

    return result;
}