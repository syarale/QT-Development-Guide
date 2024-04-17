cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(timer LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
aux_source_directory(./ timer_srcs)


add_executable(${PROJECT_NAME}
    # WIN32 # If you need a terminal for debug, please comment this statement 
    ${timer_srcs}
) 
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui) # Qt5 Shared Library