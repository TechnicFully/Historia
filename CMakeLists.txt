cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0135 NEW)
project(HistoryTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip #Last version to support C++14
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


FetchContent_Declare(
    plog
    GIT_REPOSITORY https://github.com/SergiusTheBest/plog
    GIT_TAG        1.1.10
    GIT_SHALLOW    true
)
FetchContent_MakeAvailable(plog)


enable_testing()

add_executable(historiatest historia_test.cpp)
target_link_libraries(historiatest GTest::gtest_main plog::plog)
target_compile_options(historiatest PRIVATE -Wall -W)
set_target_properties(historiatest PROPERTIES CXX_STANDARD 17)
include(GoogleTest)
#gtest_discover_tests(historiatest) #Automatically run tests after compiling
