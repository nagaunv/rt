cmake_minimum_required (VERSION 3.8)

project(rt)

# ------------------------------------------
# options
# ------------------------------------------
option(RT_BUILD_TESTS "Build Tests" ON)

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
find_package(Vulkan REQUIRED)
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
# Build fmt
# ------------------------------------------
add_subdirectory(external/fmt)

# ------------------------------------------
# Build Selene
# ------------------------------------------
add_subdirectory(external/selene)

# ------------------------------------------
# Set compiler flags
# ------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTNSIONS OFF)
if (MSVC)
  set(RT_COMPILER_OPTIONS /W4 /permissive-)
else()
  set(RT_COMPILER_OPTIONS -Wall -Wextra -g)
endif()

# ------------------------------------------
# tests
# ------------------------------------------
if (RT_BUILD_TESTS)
  add_subdirectory(test)
endif()

# ------------------------------------------
# exe
# ------------------------------------------
add_executable(
  rt
  src/main.cpp
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
# compiler options
# ------------------------------------------
target_compile_options(rt PRIVATE ${RT_COMPILER_OPTIONS})
target_compile_options(imgui_example PRIVATE ${RT_COMPILER_OPTIONS})

# ------------------------------------------
# lib
# ------------------------------------------
target_link_libraries(
  imgui_example
  glfw
  ${VULKAN_LIBRARY}
  -static
)

target_link_libraries(
  rt
  fmt
  selene::selene
  -static
)