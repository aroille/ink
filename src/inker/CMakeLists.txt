INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../ink)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glad/include)

ADD_EXECUTABLE(inker inker.cpp ../3rdparty/glad/src/glad.c)
TARGET_LINK_LIBRARIES(inker ink)
TARGET_LINK_LIBRARIES(inker glfw)

INSTALL (TARGETS inker DESTINATION ${PROJECT_BINARY_DIR}/bin)