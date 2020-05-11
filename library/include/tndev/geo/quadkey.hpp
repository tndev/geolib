#pragma once
#include <tndev/geo/tile.hpp>

#include <stdexcept>
#include <string>

namespace tndev::geo {

template <typename Projection>
inline auto tile_to_quadkey(tile<Projection>& tile) -> std::string {
    auto quadkey = std::string();

    for (size_t j = 0; j < tile.level(); j++) {
        char digit = '0';
        unsigned int i = tile.level() - static_cast<unsigned int>(j);
        unsigned int mask = 1 << (i - 1);
        if ((tile.x() & mask) != 0) {
            digit++;
        }
        if ((tile.y() & mask) != 0) {
            digit++;
            digit++;
        }
        quadkey.push_back(digit);
    }

    return quadkey;
}

template <typename Projection>
inline auto quadkey_to_tile(const std::string& quadkey) -> tile<Projection> {
    unsigned int tileX = 0;
    unsigned int tileY = 0;
    unsigned int levelOfDetail = static_cast<unsigned int>(quadkey.size());
    for (size_t j = 0; j < levelOfDetail; j++) {
        unsigned int i = levelOfDetail - static_cast<unsigned int>(j);
        unsigned int mask = 1 << (i - 1);
        switch (quadkey[levelOfDetail - i]) {
        case '0':
            break;

        case '1':
            tileX |= mask;
            break;

        case '2':
            tileY |= mask;
            break;

        case '3':
            tileX |= mask;
            tileY |= mask;
            break;

        default:
            throw std::runtime_error("Invalid QuadKey digit sequence.");
        }
    }

    return tile<Projection>(tileX, tileY, levelOfDetail);
}

} // namespace tndev::geo