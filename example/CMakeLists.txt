cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0135 NEW)
project(HistoriaExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    historia
    GIT_REPOSITORY https://github.com/TechnicFully/Historia
    GIT_TAG        dev
    GIT_SHALLOW    true
)
FetchContent_MakeAvailable(historia)



add_executable(HistoriaExample example.cpp)
target_link_libraries(HistoriaExample Historia::historia)
set_target_properties(HistoriaExample PROPERTIES CXX_STANDARD 17)
if(MSVC)
    target_compile_options(HistoriaExample PRIVATE /W4)
else()
    target_compile_options(HistoriaExample PRIVATE -Wall -Wextra -Wpedantic)
endif()

#gtest_discover_tests(historiatest) #Automatically run tests after compiling
