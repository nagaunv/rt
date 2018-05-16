# ------------------------------------------
# function Test
# ------------------------------------------
function (Test NAME LABEL)
    # add executable
    add_executable(${NAME} ${NAME}.cpp)

    # add test headers
    target_include_directories(${NAME} PRIVATE 
            "${PROJECT_SOURCE_DIR}/test")

    # add flags
    target_compile_options(${NAME} PRIVATE 
            ${RT_COMPILER_OPTIONS} 
            ${RT_TEST_COMPILER_OPTIONS})

    # add test
    add_test(NAME ${NAME} COMMAND ${NAME})

    # add labels
    set_tests_properties(${NAME} PROPERTIES LABELS ${LABEL})
endfunction()