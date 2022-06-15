# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

cmake_minimum_required(VERSION 3.5.1)

set(GRPC_FETCHCONTENT OFF)
set(GRPC_AS_SUBMODULE OFF)

include(cmake/common.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Proto file
get_filename_component(hw_proto "./proto/algointerface.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_BINARY_DIR}/algointerface.pb.cc")
set(hw_proto_hdrs "${CMAKE_BINARY_DIR}/algointerface.pb.h")
set(hw_grpc_srcs "${CMAKE_BINARY_DIR}/algointerface.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_BINARY_DIR}/algointerface.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_BINARY_DIR}"
        --cpp_out "${CMAKE_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_BINARY_DIR}")

# hw_grpc_proto
add_library(${PROJECT_NAME}
    ${hw_grpc_srcs}
    ${hw_grpc_hdrs}
    ${hw_proto_srcs}
    ${hw_proto_hdrs}
    grpc_server.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    include
    ${PROJECT_SOURCE_DIR}/src
    ${OpenCV_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${OpenCV_LIBS}
    plog
    blob-sdk-module
)