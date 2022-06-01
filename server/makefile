LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
INCLUDE_DIRS= -I /usr/local/include/ -I /usr/local/include/opencv/ -I /usr/local/include/opencv2
LIBS := ./lib/libClass.so

all: client server

client: mathtest.pb.o mathtest.grpc.pb.o client.o
	$(CXX) $^ $(LDFLAGS) -o $@ -lpthread  $(INCLUDE_DIRS) -L /usr/local/lib/libopencv_* 

server: mathtest.pb.o mathtest.grpc.pb.o server.o
	$(CXX) $^ $(LDFLAGS) -o $@ -lpthread $(INCLUDE_DIRS) -L /usr/local/lib/libopencv_* $(LIBS)
 
%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h client server
