#pragma once

#include <vector>
#include <string>
#include <sstream>

/**
 * @file cube.h
 * @brief Rubik's Cube functional representation class
 *
 * This class facilitates simulated interactions with a Rubik's Cube. A Cube
 * object may have its state manipulated through the application of one of six
 * moves provided in the Move enum for convenience.
 */
namespace rubiktrace {
    enum Face {
        UP,
        FRONT,
        RIGHT,
        LEFT,
        BACK,
        DOWN,
    };

    enum Move {
        U,
        F,
        R,
        L,
        B,
        D,
    };

    constexpr std::optional<Move> string_to_move(const std::string& str);

    struct CubeState {
        std::vector<Face> u_face;
        std::vector<Face> f_face;
        std::vector<Face> r_face;
        std::vector<Face> l_face;
        std::vector<Face> b_face;
        std::vector<Face> d_face;
    };

    class Cube {
    private:
        CubeState state;
        int distance_from_origin;
    public:
        Cube();
        Cube(const std::string& scramble);
        Cube(const CubeState& initial_state) : state(initial_state), distance_from_origin(0) {}

        void set_solved();
        void set_state(const CubeState& new_state);
        CubeState get_state() const;

        void do_move(Move move, bool do_inverse = false, int repeat = 1);
    };
}
