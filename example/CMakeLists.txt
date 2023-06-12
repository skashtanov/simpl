cmake_minimum_required(VERSION 3.8)

project(simpl_test
    DESCRIPTION "Testing of SIMPL"
    LANGUAGES CXX)

find_package(simpl CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} external_type.cpp internal.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE simpl::simpl)
