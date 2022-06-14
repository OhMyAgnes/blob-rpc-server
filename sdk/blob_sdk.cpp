#include "blob_sdk.h"

namespace smartmore
{
namespace blob
{
class BlobSDK::Impl
{
   public:
    Impl() {}

    ~Impl() = default;
    ResultCode Init()
    {
        // 这里初始化sdk持有的资源，通常是加载模型、初始化推理节点
        //
        return ResultCode::SUCCESS;
    }
    ResultCode Version(std::string& version)
    {
        version = version_;
        return ResultCode::SUCCESS;
    }

    ResultCode Run(const Request& req, Response& rsp) 
    { 
        cv::Mat gray = req.image.clone();
        if(gray.channels() == 3)
        {
            cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);
        }

        // 灰度阈值
        cv::Mat mask;
        cv::threshold(gray, mask, req.threshold, 255, cv::THRESH_BINARY);

        // 找出所有轮廓
        cv::Mat labels;
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        rsp.contours = contours;
        return ResultCode::SUCCESS; 
    }

   private:
    const std::string version_ = "v1.0.1";
};

BlobSDK::BlobSDK(): impl_(std::make_shared<Impl>()){}
BlobSDK::~BlobSDK() = default;

ResultCode BlobSDK::Init()
{
    return impl_->Init();
}

ResultCode BlobSDK::Version(std::string& version)
{
    return impl_->Version(version);
}

ResultCode BlobSDK::Run(const Request& req, Response& rsp) 
{
    return impl_->Run(req, rsp);
}

}  // namespace blob
}  // namespace smartmore