include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB CORE_SOURCES "core/*.h" "core/*.cpp")
file (GLOB MATH_SOURCES "math/*.h" "math/*.cpp")

source_group("core" FILES ${CORE_SOURCES})
source_group("math" FILES ${MATH_SOURCES})

add_library(ink STATIC ${CORE_SOURCES} ${MATH_SOURCES})

install (TARGETS ink DESTINATION ${PROJECT_BINARY_DIR}/bin)
