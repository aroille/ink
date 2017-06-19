CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )

PROJECT("INK")

### GLFW #############################

if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/3rdparty/glfw")
  message(FATAL_ERROR "The GLFW submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(src/3rdparty/glfw)

### OPENMP ############################

FIND_PACKAGE(OpenMP)

### COMPILE FLAGS #####################

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
	ADD_DEFINITIONS (/D _CRT_SECURE_NO_WARNINGS)
endif()

message ("CXX COMPILER: " ${CMAKE_CXX_COMPILER_ID})
message ("CXX FLAGS: " ${CMAKE_CXX_FLAGS})

ADD_SUBDIRECTORY(src)

