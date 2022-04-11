#pragma once

// STD includes
#include <cstdint>

// External library includes

// Project includes

struct Color {
    using channel = std::uint8_t;

    constexpr Color(const channel red, const channel green, const channel blue, const channel alpha = 255)
        :   r(red), g(green), b(blue), a(alpha)
    { }

    constexpr Color(const int color_hex, const channel alpha)
    {
        if(color_hex > 0x00FFFFFF) {
            throw std::invalid_argument("Color hex must be less than 0x00FFFFFF");
        }

        r = (color_hex >> 16) & 0xFF;
        g = (color_hex >> 8) & 0xFF;
        b = color_hex & 0xFF;
        a = alpha;
    }

    constexpr bool operator==(const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    uint8_t r, g, b, a;
};

namespace Colors {
    // useful predefined colours
    static constexpr Color BLACK {0x000000, 255};
    static constexpr Color WHITE {0xFFFFFF, 255};
    static constexpr Color RED   {0xFF0000, 255};
    static constexpr Color GREEN {0x00FF00, 255};
    static constexpr Color BLUE  {0x0000FF, 255};
}