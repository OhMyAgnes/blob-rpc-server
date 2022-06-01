//
// client.cc
// Created by zr on 2022/6/1.
//

#include <string>

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"
#include <opencv2/opencv.hpp>
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

class MathTestClient {
public:
    MathTestClient(std::shared_ptr<Channel> channel) : stub_(MathTest::NewStub(channel)) {}

    int sendRequest(std::string image, int thre) {
        MathRequest request;

        request.set_image(image);
        request.set_thre(thre);
        
        MathReply reply;

        ClientContext context;
        
        Status status = stub_->sendRequest(&context, request, &reply);
        
        if(status.ok()){
            return reply.result();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<MathTest::Stub> stub_;
};

void Run() {
    std::string address("0.0.0.0:5000");
    MathTestClient client(
            grpc::CreateChannel(
                    address,
                    grpc::InsecureChannelCredentials()
            )
    );

    int response;

    cv::Mat mat = cv::imread("/media/qulab/2fbfe086-740c-4d24-acff-839bf21fb2c2/zr/code/calca/1.jpg", cv::IMREAD_GRAYSCALE);
    std::string Image;
    std::vector<unsigned char> buff;
    cv::imencode(".jpg", mat, buff);
    Image.resize(buff.size());
    memcpy(&Image[0], buff.data(), buff.size());
   
    int Thre = 0;


    response = client.sendRequest(Image, Thre);
    std::cout << "Answer received: "  << response << std::endl;
}

int main(int argc, char* argv[]){
    Run();

    return 0;
}
