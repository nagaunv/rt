message(STATUS "------------------------------------------")

# fmt
message(STATUS "initializing fmt")
execute_process(COMMAND git submodule update --init -- external/fmt
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(external/fmt/include)

# glfw
message(STATUS "initializing glfw")
execute_process(COMMAND git submodule update --init -- external/glfw
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(external/glfw/include)

# glm
message(STATUS "initializing glm")
execute_process(COMMAND git submodule update --init -- external/glm
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(external/glm)

# imgui
message(STATUS "initializing imgui")
execute_process(COMMAND git submodule update --init -- external/imgui
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(external/imgui)

message(STATUS "------------------------------------------")