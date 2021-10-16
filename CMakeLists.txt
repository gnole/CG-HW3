cmake_minimum_required(VERSION 3.15)
project(HW3)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL)
include_directories(${SFML_INCLUDE_DIRECTORIES})

add_executable(HW3 main.cpp)
target_link_libraries(HW3 PRIVATE sfml-system sfml-window sfml-graphics OpenGL)