add_subdirectory(geometry)
add_subdirectory(rendering)
add_subdirectory(scene)

add_executable(pathtracer main.cpp)
target_link_libraries(pathtracer eigen geometry)

if(MSVC)
  target_compile_options(pathtracer PRIVATE /W4 /WX)
else()
  target_compile_options(pathtracer PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()