add_library(light_physics
  quadrature.hpp
  lens.hpp
)

target_link_libraries(light_physics eigen geometry rendering image)
target_include_directories(light_physics INTERFACE ..)

if(MSVC)
  target_compile_options(light_physics PRIVATE /W4 /WX)
else()
  target_compile_options(light_physics PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()