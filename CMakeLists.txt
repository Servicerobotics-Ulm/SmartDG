cmake_minimum_required(VERSION 2.8)
project(SmartDG)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB JS_FILES ${CMAKE_SOURCE_DIR}/js/*.js)

set(CMAKE_CXX_STANDARD 11)

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} fltk pthread)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/SmartDG)
install(FILES ${JS_FILES} DESTINATION include/SmartDG/js)
