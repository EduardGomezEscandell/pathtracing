#pragma once

// STD includes

// External library includes

// Project includes
#include "image/image.hpp"

namespace NetBPM {

enum Mode { ASCII, BINARY };

constexpr std::string_view extension_name()
{
    return "ppm";
}

std::string file_name(std::string_view base_name);


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

    friend std::ostream& operator<<(std::ostream& os, NetBPM::Output const& output)
    {
        switch (output.m_mode)
        {
        case NetBPM::ASCII: return output.ascii_impl(os);
        case NetBPM::BINARY: return output.binary_impl(os);
        }
    }

private:
    Image const& m_image;
    Mode m_mode;

    std::ostream& binary_impl(std::ostream& os) const;

    std::ostream& ascii_impl(std::ostream& os) const;
};

}