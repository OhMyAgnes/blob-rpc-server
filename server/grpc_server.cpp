#include "grpc_server.h"

#include <grpcpp/support/status.h>
#include <opencv2/core/hal/interface.h>

#include <memory>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

#include "algointerface.pb.h"
#include "blob_sdk.h"
#include "common/plog.h"
#include "plog/Log.h"

namespace smartmore
{
namespace huaxing
{
namespace server
{

cv::Mat ConvertImageToMat(algointerface::Image img)
{
    int c = img.channels();
    int w = img.height();
    int h = img.width();

    return cv::Mat(w, h, CV_8UC(c), static_cast<void*>(const_cast<char*>(img.data().data())));
}

bool ConvertBytesToMat(const std::string& str, cv::Mat& mat, int flags)
{
    int n_size = str.size();
    const char* ptr_buffer = str.data();
    cv::Mat raw_data(1, n_size, CV_8UC1, static_cast<void*>(const_cast<char*>(ptr_buffer)));
    mat = cv::imdecode(raw_data, flags);
    if (mat.data == nullptr)
    {
        PLOGE << "Convert Bytes to cvMat Failed";
        return false;
    }
    return true;
}

class InferImpl
{
   public:
    explicit InferImpl() : module_(std::make_shared<smartmore::blob::BlobSDK>()) {}
    virtual smartmore::blob::ResultCode Init()
    {
        if (module_ == nullptr)
        {
            PLOGE << "sdk module is null";
            return smartmore::blob::ResultCode::INTERNAL_ERROR;
        }
        auto res = module_->Init();
        if (res != smartmore::blob::ResultCode::SUCCESS)
        {
            PLOGE << "sdk init failed";
        }
        else
        {
            PLOGI << "sdk init succeed";
        }

        return res;
    }

    virtual smartmore::blob::ResultCode Run(const smartmore::blob::Request& req,
                                            smartmore::blob::Response& rsp)
    {
        if (module_ == nullptr)
        {
            PLOGE << "sdk module is null";
            return smartmore::blob::ResultCode::INTERNAL_ERROR;
        }

        auto res = module_->Run(req, rsp);
        if (res != smartmore::blob::ResultCode::SUCCESS)
        {
            PLOGE << "sdk run failed";
        }
        else
        {
            PLOGI << "sdk run succeed";
        }

        return res;
    }

   private:
    std::shared_ptr<smartmore::blob::BlobSDK> module_;
};

AsyncServer::AsyncServer(bool use_gpu) : use_gpu_(use_gpu), impl_(std::make_shared<InferImpl>())
{
    auto res = impl_->Init();
    if (res != smartmore::blob::ResultCode::SUCCESS)
    {
        PLOGE << "color sdk init failed";
    }
    else
    {
        PLOGI << "color sdk init succeed";
    }
}
AsyncServer::~AsyncServer() {}
Status AsyncServer::AlgoInferRun(ServerContext* context, const algointerface::AlgoInferReq* request,
                                 algointerface::AlgoInferRsp* response)
{
    if (request->has_image())
    {
        if (request->image().data().empty())
        {
            PLOGE << "algo server error: input image is empty!";
            return Status::CANCELLED;
        }
    }

    smartmore::blob::Request req{ConvertImageToMat(request->image()), request->threshold()};
    smartmore::blob::Response rsp;

    impl_->Run(req, rsp);

    response->Clear();

    for (auto& cont : rsp.contours)
    {
        auto contour = response->add_contours();
        for (auto& pt : cont)
        {
            auto point = contour->add_pts();
            point->set_x(pt.x);
            point->set_y(pt.y);
        }
    }

    return Status::OK;
}

}  // namespace server
}  // namespace huaxing
}  // namespace smartmore