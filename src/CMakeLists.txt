include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB CORE_SOURCES "core/*.h" "core/*.cpp")
file (GLOB MATH_SOURCES "math/*.h" "math/*.cpp")

source_group("core" FILES ${CORE_SOURCES})
source_group("math" FILES ${MATH_SOURCES})

add_library(ink SHARED ${CORE_SOURCES} ${MATH_SOURCES})
SET_TARGET_PROPERTIES (ink PROPERTIES DEFINE_SYMBOL "INK_EXPORT")

install (TARGETS ink DESTINATION ${PROJECT_BINARY_DIR}/bin)
