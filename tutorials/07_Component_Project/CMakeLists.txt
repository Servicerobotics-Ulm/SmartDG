cmake_minimum_required(VERSION 2.8)
project(Component_Project)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
set(CMAKE_CXX_STANDARD 11)

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES} )
target_link_libraries(${PROJECT_NAME} SmartDG fltk pthread)
target_include_directories(${PROJECT_NAME} PUBLIC "/usr/local/include/SmartDG")
