#ifndef INCLUDE_HUAXING_RPC_SERVER
#define INCLUDE_HUAXING_RPC_SERVER

#include <grpc++/alarm.h>
#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpcpp/support/status.h>

#include <memory>

#include "algointerface.grpc.pb.h"

namespace smartmore
{
namespace huaxing
{
namespace server
{

using algointerface::AlgoEngine;
using algointerface::AlgoInferReq;
using algointerface::AlgoInferRsp;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class InferImpl;

class AsyncServer final : public algointerface::AlgoEngine::Service
{
   public:
    explicit AsyncServer(bool use_gpu);
    Status AlgoInferRun(ServerContext* context, const algointerface::AlgoInferReq* request,
                        algointerface::AlgoInferRsp* response) override;

    ~AsyncServer();

   private:
    bool use_gpu_ = false;  //暂时没有用上
    std::shared_ptr<InferImpl> impl_;
};

}  // namespace server
}  // namespace huaxing
}  // namespace smartmore

#endif