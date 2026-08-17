cmake_minimum_required(3.10)
project(Historia LANGUAGES CXX)

add_library(historia STATIC historia.hpp)

target_include_directories(historia PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(Historia::historia ALIAS historia)
