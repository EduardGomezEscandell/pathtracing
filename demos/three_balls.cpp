// STD includes
#include <fstream>
#include <vector>

// External library includes

// Project includes
#include <geometry/sphere.hpp>
#include <rendering/renderable.hpp>
#include <scene/scene.hpp>
#include <image/image.hpp>
#include <image_output/netbpm_output.hpp>

int main()
{
    Scene scene
    {
        Camera{45.0},
        {
            {
                Sphere{ 1.0, Eigen::Vector3d{1, 1, 6} },
                Material{Colors::BLUE}
            },
            {
                Sphere{ 2.0, Eigen::Vector3d{2, 2, 8} },
                Material{Colors::RED}
            },
            {
                Sphere{ 0.5, Eigen::Vector3d{-1, 0, 3} },
                Material{Colors::YELLOW}
            }
        }
    };

    const auto image = scene.snap(720, 480);

    std::ofstream(NetBPM::file_name("test")) << NetBPM::Output{image} << std::endl;
}