cmake_minimum_required(VERSION 3.23)

set(VCPKG_LIBRARY_LINKAGE static CACHE STRING "Linkage of vcpkg libraries" FORCE)

project(fib-x)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    message(STATUS "Using ccache for faster builds")
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
else ()
    message(STATUS "ccache not found, proceeding without it")
endif ()

add_executable(fib src/main.cpp)

target_link_libraries(fib gmp gmpxx)