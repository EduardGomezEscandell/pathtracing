add_library(geometry
  geometry.hpp
  hit.hpp
  multi_geometry.hpp
  multi_geometry.cpp
  ray.hpp
  ray.cpp
  sphere.hpp
  sphere.cpp
  triangle.hpp
)

target_link_libraries(geometry eigen)
target_include_directories(geometry INTERFACE ..)

if(MSVC)
  target_compile_options(geometry PRIVATE /W4 /WX)
else()
  target_compile_options(geometry PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()