cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)

project("INK")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") 
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc /wd4244 /wd4996 /wd4305")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

add_subdirectory(src)
add_subdirectory(sandbox)

