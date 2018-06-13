include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ink)

ADD_EXECUTABLE(press press.cpp scene_samples.h helper_shape.h)
TARGET_LINK_LIBRARIES(press ink)

INSTALL (TARGETS press DESTINATION ${PROJECT_BINARY_DIR}/bin)