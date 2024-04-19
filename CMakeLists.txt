cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(QtDemo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64") # Qt Kit Dir

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./dialog_demo)
add_subdirectory(./action_demo)
add_subdirectory(./timer)
add_subdirectory(./mvc_pattern)
add_subdirectory(./file_system)