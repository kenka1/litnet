cmake_minimum_required(VERSION 3.25...4.3)

project(litnet VERSION 1.0.0 LANGUAGES CXX)

add_library(litnet INTERFACE)

target_include_directories(litnet INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(litnet INTERFACE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(LITNET_DEV_TOOL "Enable dev tools (tests, formatting)" ON)
endif()

if(LITNET_DEV_TOOL)
    # TESTS
    enable_testing()
    add_subdirectory(test)

    # CLANG-FORMAT
    find_program(CLANG_FORMAT NAMES clang-format-21 clang-format)

    if(CLANG_FORMAT)
        file(GLOB_RECURSE LITNET_FORMAT_SRC CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
        )

        add_custom_target(format-fix
            COMMAND ${CLANG_FORMAT} -style=file -i ${LITNET_FORMAT_SRC}
            COMMENT "Formatting litnet source files"
        )
        add_custom_target(format-check
            COMMAND ${CLANG_FORMAT} -style=file --dry-run --Werror ${LITNET_FORMAT_SRC}
            COMMENT "Checking litnet formatting"
        )
    else()
        message(STATUS "clang-format not found. Formatting targets will not be available.")
    endif()
endif()
