cmake_minimum_required(VERSION 3.1)
project(myproject)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})	
add_subdirectory(src)
add_executable(main main.cpp)
 
target_link_libraries(main mylib ${OpenCV_LIBS})
