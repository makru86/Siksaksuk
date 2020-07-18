cmake_minimum_required(VERSION 3.16)
project(Siksaksuk)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)

add_executable(Siksaksuk main.cpp)

target_link_libraries(Siksaksuk ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARIES} PNG::PNG)
target_include_directories(Siksaksuk SYSTEM PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
