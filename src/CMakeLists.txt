add_subdirectory(geometry)
add_subdirectory(rendering)
add_subdirectory(image)
add_subdirectory(image_output)
add_subdirectory(scene)

add_executable(pathtracer main.cpp)
target_link_libraries(pathtracer eigen geometry rendering image image_output scene)

if(MSVC)
  target_compile_options(pathtracer PRIVATE /W4 /WX)
else()
  target_compile_options(pathtracer PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()