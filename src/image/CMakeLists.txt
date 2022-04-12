add_library(image
  image.hpp
)

target_link_libraries(image rendering)
target_include_directories(image INTERFACE ..)

if(MSVC)
  target_compile_options(image PRIVATE /W4 /WX)
else()
  target_compile_options(image PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()