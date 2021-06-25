cmake_minimum_required(VERSION 3.17)

project(opengl_setup)

# compile dependencies
add_subdirectory(libs)

add_executable(main
  src/main.cpp
  src/common/shader.cpp src/common/shader.hpp)

# link libraries
target_link_libraries(main glfw glew glm)

# set c++17
set_target_properties(main PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO)

set(RESOURCE_FILES
  resources/color.vert resources/color.frag)

# configure resources
foreach(RESOURCE IN LISTS RESOURCE_FILES)
  configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
