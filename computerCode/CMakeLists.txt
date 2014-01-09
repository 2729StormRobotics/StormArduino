cmake_minimum_required(VERSION 2.8)

project(Arduino_LED_Control)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

set(SOURCE_DIR "src")

set(CMAKE_MODULE_PATH "/usr/local/share/Logger/;/usr/local/share/SFML/cmake/Modules/;${CMAKE_MODULE_PATH}")

set(EXECUTABLE_1_NAME "Arduino_LED_Control")

add_executable(${EXECUTABLE_1_NAME}
               	${SOURCE_DIR}/main.cpp)

find_package(SFML 2 REQUIRED system network)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_1_NAME} ${SFML_LIBRARIES})
endif()

find_package(Logger REQUIRED)
target_link_libraries(${EXECUTABLE_1_NAME} Logger)
