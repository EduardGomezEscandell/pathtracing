add_library(light_physics
  constexpr_math.hpp
  quadrature.hpp
  lens.hpp
  refraction.hpp
)

set_target_properties(light_physics PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(light_physics eigen)
target_include_directories(light_physics INTERFACE ..)

if(MSVC)
  target_compile_options(light_physics PRIVATE /W4 /WX)
else()
  target_compile_options(light_physics PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()