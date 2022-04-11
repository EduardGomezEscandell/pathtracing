add_library(rendering
  color.hpp
  material.hpp
  renderable.hpp
)

target_link_libraries(rendering eigen geometry)
target_include_directories(rendering INTERFACE ..)

if(MSVC)
  target_compile_options(rendering PRIVATE /W4 /WX)
else()
  target_compile_options(rendering PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()