set(BIN_NAME lesson6)

set(SRCS main.cpp texture.cpp)

add_executable(${BIN_NAME} WIN32 ${SRCS})

target_link_libraries(${BIN_NAME} "opengl32.lib" "glu32.lib")
