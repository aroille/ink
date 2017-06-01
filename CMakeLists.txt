cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project("INK")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(warnings "-Wall -Wextra -Werror")
	set(cxx_flags "-std=c++11 -fopenmp")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(warnings "-Wall -Wextra -Werror")
	set(cxx_flags "-std=c++11 -fopenmp -I/usr/lib/gcc/x86_64-linux-gnu/4.9/include")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(warnings "/W4 /WX")
	set(cxx_flags "")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${cxx_flags} ${OpenMP_CXX_FLAGS}")

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

add_subdirectory(src)

