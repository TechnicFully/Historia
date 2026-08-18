cmake_minimum_required(VERSION 3.10)
project(Historia LANGUAGES CXX)

add_library(historia INTERFACE historia.hpp)

target_include_directories(historia INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(Historia::historia ALIAS historia)
