add_library(geometry
  geometry.hpp
  hit.hpp
  ray.hpp
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