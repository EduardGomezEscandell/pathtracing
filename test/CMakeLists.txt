add_executable(run_tests test_main.cpp)

target_link_libraries(run_tests doctest eigen geometry rendering scene image image_output)

add_subdirectory(test_geometry test_rendering)

if(MSVC)
  target_compile_options(run_tests PRIVATE /W3 /WX)
else()
  target_compile_options(run_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()