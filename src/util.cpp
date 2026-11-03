#include <vector>
#include "cube.h"

using namespace rubiktrace;

bool is_face_symmetric(const std::vector<Sticker>& face) {
    return face[1] == face[3] == face[5] == face[7] && face[0] == face[2] == face[6] == face[8];
}

void rotate_face_stickers(std::vector<Sticker>& vec, const bool clockwise = true) {
    std::vector<Sticker> rotated(9);

    // Transpose and reverse rows
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int i = r * 3 + c;
            int j;

            if (clockwise) {
                j = c * 3 + (2 - r);
            } else {
                j = (2 - c) * 3 + r;
            }

            rotated[j] = vec[i];
        }
    }

    vec = rotated;
}
