#include "../include/cube.h"

using namespace rubiktrace;

constexpr std::optional<Move> string_to_move(const std::string& str) {
    if (str == "U") return U;
    if (str == "F") return F;
    if (str == "R") return R;
    if (str == "L") return L;
    if (str == "B") return B;
    if (str == "D") return D;
    return std::nullopt;
}

Cube::Cube() : distance_from_origin(0) {}

Cube::Cube(const std::string& scramble) : distance_from_origin(0) {
    this->state = CubeState();
    this->set_solved();

    std::istringstream scramble_stream(scramble);
    std::string move_sub;
    while (scramble_stream >> move_sub) {
        bool do_inverse = false;
        int repeat = 1;
        if (char move_suffix = move_sub.back(); move_suffix == '\'') {
            do_inverse = true;
        } else if (move_suffix == '2') {
            repeat = 2;
        }
        Move move = string_to_move(move_sub).value();
        this->do_move(move, do_inverse, repeat);
    }
}

void Cube::set_solved() {
    this->state.u_face = std::vector<Face>(9, UP);
    this->state.f_face = std::vector<Face>(9, FRONT);
    this->state.r_face = std::vector<Face>(9, RIGHT);
    this->state.l_face = std::vector<Face>(9, LEFT);
    this->state.b_face = std::vector<Face>(9, BACK);
    this->state.d_face = std::vector<Face>(9, DOWN);
}

void Cube::set_state(const CubeState& new_state) { this->state = new_state; }
CubeState Cube::get_state() const { return this->state; }

void Cube::do_move(Move move, bool do_inverse, int repeat) {
    for (int i = 0; i < repeat; i++) {
        // U move
        // U and D faces are unchanged
        // TODO: State transitions
        CubeState* cube_state = &this->state;
        switch (move) {
            case U: {
                std::vector<Face> original_l_face = cube_state->l_face;
                cube_state->l_face[0] = cube_state->f_face[0];
                cube_state->l_face[1] = cube_state->f_face[1];
                cube_state->l_face[2] = cube_state->f_face[2];

                cube_state->f_face[0] = cube_state->r_face[0];
                cube_state->f_face[1] = cube_state->r_face[1];
                cube_state->f_face[2] = cube_state->r_face[2];

                cube_state->r_face[0] = cube_state->b_face[8];
                cube_state->r_face[1] = cube_state->b_face[7];
                cube_state->r_face[2] = cube_state->b_face[6];

                cube_state->b_face[8] = original_l_face[0];
                cube_state->b_face[7] = original_l_face[1];
                cube_state->b_face[6] = original_l_face[2];
                break;
            }
            case F: {
                std::vector<Face> original_u_face = cube_state->u_face;
                cube_state->u_face[6] = cube_state->l_face[8];
                cube_state->u_face[7] = cube_state->l_face[5];
                cube_state->u_face[8] = cube_state->l_face[2];

                cube_state->l_face[2] = cube_state->d_face[0];
                cube_state->l_face[5] = cube_state->d_face[1];
                cube_state->l_face[8] = cube_state->d_face[2];

                cube_state->d_face[0] = cube_state->r_face[6];
                cube_state->d_face[1] = cube_state->r_face[3];
                cube_state->d_face[2] = cube_state->r_face[0];

                cube_state->r_face[0] = original_u_face[6];
                cube_state->r_face[3] = original_u_face[7];
                cube_state->r_face[6] = original_u_face[8];
                break;
            }
            case R:
                break;
            case L:
                break;
            case B:
                break;
            case D:
                break;
        }

        if (do_inverse) {

        }
    }
}