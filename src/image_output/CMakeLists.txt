add_library(image_output
  netbpm_output.hpp
  netbpm_output.cpp
)

target_link_libraries(image_output image)
target_include_directories(image_output INTERFACE ..)

if(MSVC)
  target_compile_options(image_output PRIVATE /W4 /WX)
else()
  target_compile_options(image_output PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()