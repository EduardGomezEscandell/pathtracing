add_library(scene
  camera.hpp
  scene.hpp
)

target_link_libraries(scene eigen geometry rendering)
target_include_directories(scene INTERFACE ..)

if(MSVC)
  target_compile_options(scene PRIVATE /W4 /WX)
else()
  target_compile_options(scene PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()