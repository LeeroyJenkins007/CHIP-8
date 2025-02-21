cmake_minimum_required(VERSION 3.20)

project(Chip8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


set(EXECUTABLE_NAME ${PROJECT_NAME})

add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)


add_executable(${EXECUTABLE_NAME} emulator.cpp Chip8.cpp Chip8.h Platform.cpp Platform.h MyGui.cpp MyGui.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/imgui_docking)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/imgui_docking/backends)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/SDL)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3)