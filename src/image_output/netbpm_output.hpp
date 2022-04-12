#pragma once

// STD includes

// External library includes

// Project includes
#include "image/image.hpp"

namespace NetBPM {

constexpr std::string_view extension_name()
{
    return "ppm";
}

std::string file_name(std::string_view base_name)
{
    std::stringstream ss;
    ss << base_name << "." << extension_name();
    return ss.str();
}

enum Mode { ASCII, BINARY };


class Output
{
public:
    Output(Image const& image, Mode mode = ASCII) :
        m_image(image), m_mode(mode)
    { }

    Mode get_mode() const
    {
        return m_mode;
    }

    void set_mode(Mode mode)
    {
        m_mode = mode;
    }

    friend std::ostream& operator<<(std::ostream& os, Output const& output)
    {
        switch (output.m_mode)
        {
        case ASCII: return output.ascii_impl(os);
        case BINARY: return output.binary_impl(os);
        }
    }

private:

    Image const& m_image;
    Mode m_mode;

    std::ostream& binary_impl(std::ostream& os) const
    {
        return os << "Binary mode not yet implemented" << std::endl;
    }

    std::ostream& ascii_impl(std::ostream& os) const
    {
        os << "P3\n"
           << m_image.width() << " " << m_image.height() << "\n"
           << 255 << "\n";

        for(auto const& pixel: m_image)
        {
            os << static_cast<int>(pixel.r) << " "
               << static_cast<int>(pixel.g) << " "
               << static_cast<int>(pixel.b) << " ";
        }
        return os << '\n';
    }
};

}