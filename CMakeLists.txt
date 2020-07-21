cmake_minimum_required(VERSION 3.16)
project(Siksaksuk)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(dependencies/soil)

add_executable(Siksaksuk
        main.cpp
        Player.h
        include/tk/Image.h
        include/tk/Render.h
        include/tk/Animation.h
        include/tk/Clock.h
        source/Image.cpp)

target_link_libraries(Siksaksuk PUBLIC ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARIES} soil)
target_include_directories(Siksaksuk SYSTEM PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_include_directories(Siksaksuk PUBLIC include)
target_compile_options(Siksaksuk PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>)

add_subdirectory(../SFML SFML EXCLUDE_FROM_ALL)
add_subdirectory(../box2d box2d EXCLUDE_FROM_ALL)
