// STD includes
#include <fstream>

// External library includes
#include <Eigen/Dense>

// Project includes
#include <geometry/sphere.hpp>
#include <scene/scene.hpp>
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

    std::ofstream(NetBPM::file_name("demo_three_balls")) << NetBPM::Output{image} << std::endl;
}