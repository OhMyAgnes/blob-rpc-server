// 
// server.cc
// Created by zr on 2022/6/1.
//

#include <string>
#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"
#include "myclass.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

class MathServiceImplementation final : public MathTest::Service {
    Status sendRequest(
            ServerContext* context,
            const MathRequest* request,
            MathReply* reply
    ) override {
        std::string Image = request->image();
        int Thre = request->thre();
        std::vector<unsigned char>vec_data(Image.c_str(),Image.c_str()+Image.size());
       
        cv::Mat src = cv::imdecode(vec_data,CV_LOAD_IMAGE_GRAYSCALE);
        
        ReadImage MyClass(Thre, src);
        reply->set_result(MyClass.getSum());

        return Status::OK;
    }
};

void Run() {
    std::string address("0.0.0.0:5000");
    MathServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}
