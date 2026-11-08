#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>
#include <vector>
#include <string>
#include "../include/cube.h"
#include "../include/inference.h"

using namespace rubiktrace;

TEST_CASE("Test known algorithms") {
    SUBCASE("T-Perm") {
        const std::string alg = "R U R' U' R' F R2 U' R' U' R U R' F'";

        Cube cube(alg);
        CubeState initial_state = cube.get_state();

        std::istringstream scramble_stream(alg);
        std::string move_sub;
        std::vector<Face> observed_face_sequence;
        Algorithm solution_algorithm;

        while (scramble_stream >> move_sub) {
            bool do_inverse = false;
            int repeat = 1;
            if (char move_suffix = move_sub.back(); move_suffix == '\'') {
                do_inverse = true;
            } else if (move_suffix == '2') {
                repeat = 2;
            }
            std::string layer_move(1, move_sub[0]);
            Layer layer = string_to_move(layer_move).value();
            auto move = Move{layer, do_inverse, repeat};
            solution_algorithm.push_back(move);
            cube.do_move(move);
            observed_face_sequence.push_back(cube.get_state().f_face);
        }

        std::vector<CandidateState> inferred_state_sequence = infer(initial_state, observed_face_sequence);

        Algorithm inferred_solution_algorithm = inferred_state_sequence.back().transition_from_origin;

        CHECK_EQ(inferred_solution_algorithm, solution_algorithm);
    }
}