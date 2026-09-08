#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/cube.h"

using namespace rubiktrace;

TEST_CASE("Test cube initialisations") {
    SUBCASE("Test empty constructor") {
        CubeState solved_state;
        solved_state.u_face = std::vector<Sticker>(9, UP);
        solved_state.f_face = std::vector<Sticker>(9, FRONT);
        solved_state.r_face = std::vector<Sticker>(9, RIGHT);
        solved_state.l_face = std::vector<Sticker>(9, LEFT);
        solved_state.b_face = std::vector<Sticker>(9, BACK);
        solved_state.d_face = std::vector<Sticker>(9, DOWN);

        Cube test_cube{};
        CubeState test_state = test_cube.get_state();

        CHECK_EQ(test_state, solved_state);
    }
}