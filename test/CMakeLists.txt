cmake_minimum_required(VERSION 3.10)	
cmake_policy(SET CMP0135 NEW)
project(HistoriaTest)

set(CMAKE_CXX_STANDARD 17)
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
    GIT_TAG        1.1.11
    GIT_SHALLOW    true
)
FetchContent_MakeAvailable(plog)


FetchContent_Declare(
    historia
    GIT_REPOSITORY https://github.com/TechnicFully/Historia
    GIT_TAG        main
    GIT_SHALLOW    true
)
FetchContent_MakeAvailable(historia)


enable_testing()


### Speedtest executable ###
add_executable(historiaspeedtest historia_speedtest.cpp)
set_target_properties(historiaspeedtest PROPERTIES CXX_STANDARD 17)
target_link_libraries(historiaspeedtest PRIVATE Historia::historia)
if (MSVC)
	target_compile_options(historiaspeedtest PRIVATE -Wall /W4 /WX /permissive-)
else()
	target_compile_options(historiaspeedtest PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror)
endif()


### Test executable ###
add_executable(historiatest historia_test.cpp)
set_target_properties(historiatest PROPERTIES CXX_STANDARD 17)
target_link_libraries(historiatest PRIVATE GTest::gtest_main plog::plog Historia::historia)
if (MSVC)
	target_compile_options(historiatest PRIVATE -Wall /W4 /WX /permissive-)
else()
	target_compile_options(historiatest PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror)
endif()


include(GoogleTest)
#gtest_discover_tests(historiatest) #Automatically run tests after compiling
