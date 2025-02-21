cmake_minimum_required(VERSION 3.20)

project(Chip8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(IMGUI_PATH "thirdparty/imgui_docking")



set(EXECUTABLE_NAME ${PROJECT_NAME})

add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)



add_executable(${EXECUTABLE_NAME} emulator.cpp Chip8.cpp Chip8.h Platform.cpp Platform.h MyGui.cpp MyGui.h)

# adds ImGui core files
target_sources(${EXECUTABLE_NAME} PRIVATE 
            ${IMGUI_PATH}/imgui.cpp
            ${IMGUI_PATH}/imgui_draw.cpp
            ${IMGUI_PATH}/imgui_widgets.cpp
            ${IMGUI_PATH}/imgui_tables.cpp
            ${IMGUI_PATH}/imgui_demo.cpp
)  

# adds SDL3 backend implementaion
target_sources(${EXECUTABLE_NAME} PRIVATE
    ${IMGUI_PATH}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_PATH}/backends/imgui_impl_sdlrenderer3.cpp
)

# Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${IMGUI_PATH}
    ${IMGUI_PATH}/backends
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/SDL)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3)