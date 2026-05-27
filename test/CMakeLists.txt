add_executable(unit_tests
    main_test.cpp
)

set(DEBUG_FLAGS
    -Wall -Wextra -Wpedantic
    -Wconversion -Wsign-conversion
    -Wold-style-cast -Werror -g
    -fsanitize=address,undefined
)

target_compile_options(unit_tests PRIVATE
    $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
    $<$<CONFIG:Release>:-O2>
)

target_link_options(unit_tests PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

target_link_libraries(unit_tests PRIVATE
    litnet
)
