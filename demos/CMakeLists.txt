add_executable(three_balls three_balls.cpp)
target_link_libraries(three_balls eigen geometry rendering image image_output scene)

if(MSVC)
  target_compile_options(three_balls PRIVATE /W4 /WX)
else()
  target_compile_options(three_balls PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

message("${CMAKE_CURRENT_BINARY_DIR}/three_balls")
message("${BIN_DIR}/three_balls")
