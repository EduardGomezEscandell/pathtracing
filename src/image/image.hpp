#pragma once

// STD includes
#include <array>

// External library includes
#include <Eigen/Dense>

// Project includes


template<std::size_t TWidth, std::size_t THeight>
struct Image {
    static constexpr std::size_t width = TWidth;
    static constexpr std::size_t height = THeight;

    std::array<std::array<Color, width>, height> pixels;

    constexpr Color& operator()(std::size_t row, std::size_t col)
    {
    #ifndef NDEBUG
        if(row > height) throw std::invalid_argument("Row index out of bounds");
        if(col > width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return pixels[row][col];
    }

    constexpr Color const& operator()(std::size_t row, std::size_t col) const
    {
    #ifndef NDEBUG
        if(row > height) throw std::invalid_argument("Row index out of bounds");
        if(col > width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return pixels[row][col];
    }
};