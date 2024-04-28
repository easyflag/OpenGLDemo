set(BIN_NAME lesson4)

add_executable(${BIN_NAME} WIN32 main.cpp)

target_link_libraries(${BIN_NAME} "opengl32.lib" "glu32.lib")
