cmake_minimum_required(VERSION 3.11)
project(RotatingCircles)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Path to the local raylib repository
#IMPORTANT: Change this to the path of your raylib repository
set(RAYLIB_DIR "/home/tanay/raylib")
#============================================================

# Add raylib
add_subdirectory(${RAYLIB_DIR} raylib)

include_directories(${RAYLIB_DIR}/src)

# Our Project
add_executable(${PROJECT_NAME} main.c actors.c actors.h)
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
