cmake_minimum_required (VERSION 3.8)

project(rt)

# ------------------------------------------
# Enable CTest
# ------------------------------------------
include (CTest)
enable_testing()

# ------------------------------------------
# Enable ExternalProject
# ------------------------------------------
include(ExternalProject)

# ------------------------------------------
# Find Vulkan (requires Vulkan SDK)
# ------------------------------------------
find_package(Vulkan)
set(VULKAN_INCLUDE_DIR ${Vulkan_INCLUDE_DIR})
set(VULKAN_LIBRARY ${Vulkan_LIBRARY})
include_directories(rt ${VULKAN_INCLUDE_DIR})

# ------------------------------------------
# Initialize submodules
# ------------------------------------------
include(external/external.cmake)

# ------------------------------------------
# Build GLFW
# ------------------------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# ------------------------------------------
# Set compiler flags
# ------------------------------------------
if (MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /permissive- /std:c++latest")
else()
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -g -static")
endif()

# ------------------------------------------
# exe
# ------------------------------------------
add_executable(
  rt
  src/main.cpp
  external/fmt/src/format.cc
)

add_executable(
  imgui_example
  external/imgui/examples/vulkan_example/main.cpp
  external/imgui/examples/vulkan_example/imgui_impl_glfw_vulkan.cpp
  external/imgui/imgui.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_demo.cpp
)

# ------------------------------------------
# lib
# ------------------------------------------
target_link_libraries(
  imgui_example
  glfw
  ${VULKAN_LIBRARY}
)