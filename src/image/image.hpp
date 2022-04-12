#pragma once

// STD includes
#include <array>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "rendering/color.hpp"


class Image 
{
public:
    Image(const std::size_t width, std::size_t height)
        : m_height(height), m_width(width), m_pixels(width * height, Colors::BLACK)
    {  }

    constexpr Color& operator()(std::size_t row, std::size_t col)
    {
    #ifndef NDEBUG
        if(row > m_height) throw std::invalid_argument("Row index out of bounds");
        if(col > m_width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return m_pixels[row*m_width + col];
    }

    constexpr Color const& operator()(std::size_t row, std::size_t col) const
    {
    #ifndef NDEBUG
        if(row > m_height) throw std::invalid_argument("Row index out of bounds");
        if(col > m_width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return m_pixels[row*m_width + col];
    }

    auto begin() { return m_pixels.begin(); }
    auto end() { return m_pixels.end(); }

    auto cbegin() const { return m_pixels.cbegin(); }
    auto cend() const { return m_pixels.cend(); }

    auto begin() const { return cbegin(); }
    auto end() const { return cend(); }

    auto width() const noexcept { return m_width; }
    auto height() const noexcept { return m_height; }

private:
    std::size_t m_height;
    std::size_t m_width;
    std::vector<Color> m_pixels;
};