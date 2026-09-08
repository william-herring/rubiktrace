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
    SUBCASE("Scramble string constructor") {
        CubeState scrambled_state;
        scrambled_state.u_face = { UP, UP, UP, UP, UP, UP, DOWN, DOWN, UP };
        scrambled_state.f_face = { RIGHT, RIGHT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, LEFT };
        scrambled_state.r_face = { RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, BACK, BACK, FRONT };
        scrambled_state.l_face = { FRONT, FRONT, BACK, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT };
        scrambled_state.b_face = { BACK, BACK, RIGHT, BACK, BACK, BACK, LEFT, LEFT, BACK };
        scrambled_state.d_face = { DOWN, DOWN, UP, DOWN, DOWN, UP, DOWN, DOWN, DOWN };

        std::string scramble = "R2 U R2";

        Cube test_cube(scramble);
        CubeState test_state = test_cube.get_state();
        CHECK_EQ(test_state, scrambled_state);
    }
    SUBCASE("Initialise with WR scramble") {
        CubeState scrambled_state;
        scrambled_state.u_face = { RIGHT, LEFT, LEFT, UP, UP, UP, DOWN, FRONT, UP };
        scrambled_state.f_face = { FRONT, DOWN, FRONT, UP, FRONT, RIGHT, FRONT, RIGHT, DOWN };
        scrambled_state.r_face = { RIGHT, RIGHT, UP, FRONT, RIGHT, RIGHT, RIGHT, DOWN, LEFT };
        scrambled_state.l_face = { UP, FRONT, RIGHT, UP, LEFT, LEFT, LEFT, LEFT, LEFT };
        scrambled_state.b_face = { DOWN, DOWN, DOWN, BACK, BACK, BACK, BACK, BACK, BACK };
        scrambled_state.d_face = { FRONT, DOWN, BACK, FRONT, DOWN, BACK, FRONT, LEFT, BACK };

        std::string scramble = "L B R2 B' R2 U2 F D R2 U R2 F2 D2 R U B L2";
        Cube test_cube(scramble);
        CubeState test_state = test_cube.get_state();
        CHECK_EQ(test_state, scrambled_state);
    }
}