include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ink)

add_executable(viewer viewer.cpp)
target_link_libraries(viewer ink)
target_link_libraries(viewer glfw)

install (TARGETS viewer DESTINATION ${PROJECT_BINARY_DIR}/bin)