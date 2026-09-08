#pragma once

#include <utility>
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
    enum Sticker {
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

    std::optional<Move> string_to_move(const std::string& str);

    // The order of entries in these face vectors should reflect a flat cube net
    // It would be good to have some kind of logic to ensure state validity, although this step is implied
    // so long as the state is manipulated by interfacing with a Cube object.
    struct CubeState {
        std::vector<Sticker> u_face;
        std::vector<Sticker> f_face;
        std::vector<Sticker> r_face;
        std::vector<Sticker> l_face;
        std::vector<Sticker> b_face;
        std::vector<Sticker> d_face;

        bool operator==(const CubeState&) const = default;
    };

    class Cube {
    private:
        CubeState state;
        int distance_from_origin;
    public:
        Cube();
        Cube(const std::string& scramble);
        Cube(CubeState  initial_state) : state(std::move(initial_state)), distance_from_origin(0) {}

        void set_solved();
        void set_state(const CubeState& new_state);
        CubeState get_state() const;

        void do_move(Move move, bool do_inverse = false, int repeat = 1);
    };
}
