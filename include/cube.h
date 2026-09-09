#pragma once

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
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

    enum Layer {
        U,
        F,
        R,
        L,
        B,
        D,
    };

    struct Move {
        Layer layer;
        bool do_inverse;
        int repeat;
    };

    std::optional<Layer> string_to_move(const std::string& str);

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

        static std::optional<std::string> sticker_to_string(const Sticker& sticker);
        static std::string format_face_vector(const std::vector<Sticker>& face_vector, int alignment_spacing = 0);

        bool operator==(const CubeState&) const = default;
        friend std::ostream& operator<<(std::ostream& os, const CubeState& cube) {
            os << format_face_vector(cube.u_face) << "\n---\n";
            os << format_face_vector(cube.l_face) << "\n---\n";
            os << format_face_vector(cube.f_face) << "\n---\n";
            os << format_face_vector(cube.r_face) << "\n---\n";
            os << format_face_vector(cube.d_face) << "\n---\n";
            os << format_face_vector(cube.b_face) << "\n---\n";
            return os;
        }
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

        void do_move(Move move);
    };
}
