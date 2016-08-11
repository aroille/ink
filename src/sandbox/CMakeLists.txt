include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ink)

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox ink)

install (TARGETS sandbox DESTINATION ${PROJECT_BINARY_DIR}/bin)