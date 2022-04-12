// STD includes

// External library includes

// Project includes
#include "image/image.hpp"
#include "netbpm_output.hpp"


namespace NetBPM {

std::string file_name(std::string_view base_name)
{
    std::stringstream ss;
    ss << base_name << "." << extension_name();
    return ss.str();
}

std::ostream& Output::binary_impl(std::ostream& os) const
{
    return os << "Binary mode not yet implemented" << std::endl;
}

std::ostream& Output::ascii_impl(std::ostream& os) const
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

}