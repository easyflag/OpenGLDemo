cmake_minimum_required(VERSION 3.5.0)
project(lesson VERSION 0.1.0)

set(SRCS main.cpp texture.cpp)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})

target_link_libraries(${PROJECT_NAME} "opengl32.lib" "glu32.lib")
