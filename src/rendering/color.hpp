#pragma once

// STD includes
#include <cstdint>
#include <concepts>

// External library includes

// Project includes

struct Color {
    using channel = std::uint8_t;

    constexpr Color()
    {
        // Black by default
        r = 0x00;
        g = 0x00;
        b = 0x00;
        a = 0xFF;
    };

    constexpr Color(const channel red, const channel green, const channel blue, const channel alpha = 255)
        :   r(red), g(green), b(blue), a(alpha)
    { }

    template<std::integral R, std::integral G, std::integral B, std::integral A>
    constexpr Color(const R red, const G green, const B blue, const A alpha = 255)
        :   r(static_cast<channel>(red)),
            g(static_cast<channel>(green)),
            b(static_cast<channel>(blue)),
            a(static_cast<channel>(alpha))
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

    constexpr bool operator!=(const Color& other) const
    {
        return !(*this == other);
    }


    uint8_t r, g, b, a;
};

std::ostream& operator<<(std::ostream& os, Color const& color)
{
    os << "Color("
       << static_cast<int>(color.r) << ", "
       << static_cast<int>(color.g) << ", "
       << static_cast<int>(color.b) << ", "
       << static_cast<int>(color.a) << ")";
    return os;
}

namespace Colors {
    // useful predefined colours
    static constexpr Color BLACK   {0x000000, 255};
    static constexpr Color WHITE   {0xFFFFFF, 255};

    static constexpr Color RED     {0xFF0000, 255};
    static constexpr Color GREEN   {0x00FF00, 255};
    static constexpr Color BLUE    {0x0000FF, 255};

    static constexpr Color YELLOW  {0xFFFF00, 255};
    static constexpr Color CYAN    {0x00FFFF, 255};
    static constexpr Color MAGENTA {0xFF00FF, 255};
}