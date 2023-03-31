# TODO: decrease minimum required version
cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(stack_pimpl
    DESCRIPTION "Fast stack implementation of PIMPL idiom"
    VERSION 0.1.0
    LANGUAGES CXX
)
    
option(BUILD_STATIC "Enables building header only library" ON)
option(BUILD_SHARED "Enables building an dll library" OFF)
option(RUN_CLANG_TIDY "Enables clang-tidy analysis in Debug mode" OFF)

list(APPEND Sources src/stack_pimpl.cpp)

message(STATUS "Build options: ${CMAKE_CXX_FLAGS_RELEASE}")

if (BUILD_STATIC)
    message(STATUS "Building a static library")
    add_library(${PROJECT_NAME} STATIC ${Sources})
endif()

if (BUILD_SHARED)
    message(STATUS "Building a shared library")
    add_library(${PROJECT_NAME} SHARED ${Sources})
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES 
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)

if (RUN_CLANG_TIDY)
    if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
        message(STATUS "Unable to run clang-tidy when source dir equal binary dir")
    else()
        message(STATUS "Starting clang-tidy diagnostics")
        set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*,clang-analyzer-*,-clang-analyzer-cplusplus* --use-color)
    endif()
endif()

unset(Sources)
