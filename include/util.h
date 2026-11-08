#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "inference.h"
#include "cube.h"

using namespace rubiktrace;

inline std::string algorithm_to_string(const Algorithm& algorithm) {
    std::ostringstream ss;
    for (auto& move : algorithm) {
        ss << move.to_string() << " ";
    }
    return ss.str();
}

inline void rotate_face_stickers(std::vector<Sticker>& vec, const bool clockwise = true) {
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
