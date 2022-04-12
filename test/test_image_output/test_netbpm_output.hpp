#pragma once

// STD includes
#include <fstream>
#include <sstream>

// External library includes
#include <doctest/doctest.h>

// Project includes
#include "image/image.hpp"
#include "image_output/netbpm_output.hpp"


TEST_CASE("NetBPM output")
{

    SUBCASE("Write to disk")
    {
        /*
         * This test is disabled because unit tests should avoid touching the
         * disk. Left here for reference.
         */

        // static constexpr std::size_t w = 480;
        // static constexpr std::size_t h = 270;

        // Image<w, h> image;

        // for(std::size_t row=0; row<h; ++row)
        // {
        //     for(std::size_t col=0; col<w; ++col)
        //     {
        //         image(row, col) = Color(255*row/h, 255*col/w, 0);
        //     }
        // }

        // std::ofstream(NetBPM::file_name("test")) << NetBPM::Output{image} << std::endl;
    }

    SUBCASE("ASCII")
    {
        static constexpr std::size_t w = 16;
        static constexpr std::size_t h = 9;

        Image<w, h> image;

        for(std::size_t row=0; row<h; ++row)
        {
            for(std::size_t col=0; col<w; ++col)
            {
                image(row, col) = Color(255*row/h, 255*col/w, 128); // Colour gradient
            }
        }

        std::stringstream ss;
        ss << NetBPM::Output{image};

        static constexpr std::string_view reference =
            "P3\n"
            "16 9\n"
            "255\n"
            "0 0 128 0 15 128 0 31 128 0 47 128 0 63 128 0 79 128 0 95 128 0 111 128 0 127 128 0 143 128 0 159 128 0 175 128 0 191 128 0 207 128 0 223 128 0 239 128 \n"
            "28 0 128 28 15 128 28 31 128 28 47 128 28 63 128 28 79 128 28 95 128 28 111 128 28 127 128 28 143 128 28 159 128 28 175 128 28 191 128 28 207 128 28 223 128 28 239 128 \n"
            "56 0 128 56 15 128 56 31 128 56 47 128 56 63 128 56 79 128 56 95 128 56 111 128 56 127 128 56 143 128 56 159 128 56 175 128 56 191 128 56 207 128 56 223 128 56 239 128 \n"
            "85 0 128 85 15 128 85 31 128 85 47 128 85 63 128 85 79 128 85 95 128 85 111 128 85 127 128 85 143 128 85 159 128 85 175 128 85 191 128 85 207 128 85 223 128 85 239 128 \n"
            "113 0 128 113 15 128 113 31 128 113 47 128 113 63 128 113 79 128 113 95 128 113 111 128 113 127 128 113 143 128 113 159 128 113 175 128 113 191 128 113 207 128 113 223 128 113 239 128 \n"
            "141 0 128 141 15 128 141 31 128 141 47 128 141 63 128 141 79 128 141 95 128 141 111 128 141 127 128 141 143 128 141 159 128 141 175 128 141 191 128 141 207 128 141 223 128 141 239 128 \n"
            "170 0 128 170 15 128 170 31 128 170 47 128 170 63 128 170 79 128 170 95 128 170 111 128 170 127 128 170 143 128 170 159 128 170 175 128 170 191 128 170 207 128 170 223 128 170 239 128 \n"
            "198 0 128 198 15 128 198 31 128 198 47 128 198 63 128 198 79 128 198 95 128 198 111 128 198 127 128 198 143 128 198 159 128 198 175 128 198 191 128 198 207 128 198 223 128 198 239 128 \n"
            "226 0 128 226 15 128 226 31 128 226 47 128 226 63 128 226 79 128 226 95 128 226 111 128 226 127 128 226 143 128 226 159 128 226 175 128 226 191 128 226 207 128 226 223 128 226 239 128 \n";

        CHECK_EQ(ss.str(), reference);
    }
}