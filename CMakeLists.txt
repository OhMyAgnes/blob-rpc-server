cmake_minimum_required(VERSION 3.18.0)
project(blob-rpc-server VERSION 1.0.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# set cv path to local dir
if(WIN32)
set(OpenCV_URL ${PROJECT_SOURCE_DIR}/3rdparty/opencv-4.2.0-windows.zip)
else()
set(OpenCV_URL ${PROJECT_SOURCE_DIR}/3rdparty/opencv-4.2.0-linux-x64.tar.gz)
endif()

include(fetch/OpenCV)

add_subdirectory(sdk)
add_subdirectory(server)
add_subdirectory(tests)