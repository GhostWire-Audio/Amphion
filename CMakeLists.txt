cmake_minimum_required(VERSION 4.1)
project(Amphion)

set(CMAKE_CXX_STANDARD 20)

include (FetchContent)

FetchContent_Declare(
        portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
        GIT_TAG master
)

FetchContent_MakeAvailable(portaudio)

add_executable(Amphion main.cpp
        src/AudioNode.h)
target_link_libraries(Amphion PRIVATE portaudio)

add_custom_command(TARGET Amphion POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:portaudio>
        $<TARGET_FILE_DIR:Amphion>
)
