/**
 * @file blob_sdk.h
 * @author zhenkun.yu (zhenkun.yu@smartmore.com)
 * @brief
 * @version 1.0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022 SmartMore
 *
 */
#ifndef BLOB_SDK_H
#define BLOB_SDK_H

#include <vector>
#ifdef _MSC_VER
#ifdef SM_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API
#endif

#include <memory>
#include <opencv2/opencv.hpp>
#include <vector>

namespace smartmore
{
namespace blob
{
enum class ResultCode
{
    SUCCESS = 0,
    BAD_INPUT = 1,
    INTERNAL_ERROR = 2
};

using contour = std::vector<cv::Point>;

/**
 * @brief 输入数据全部放在这个结构体，
 *        需要增加参数时，只用修改结构体定义，不需要改函数
 *
 * @param image 输入图片
 * @param threshold 输入的阈值
 */
struct Request
{
    cv::Mat image;
    float threshold;
};

/**
 * @brief 输入结构
 *
 * @param contours 输出的轮廓数组
 * @param threshold 输入的阈值
 */
struct Response
{
    std::vector<contour> contours;
};

class BlobSDK
{
   public:
    /**
     * @brief 初始化sdk的所有资源。整个生命周期只用调用一次
     *
     * @return ResultCode
     */
    ResultCode Init();
    /**
     * @brief 获取版本号
     *
     * @param version 版本号
     * @return ResultCode
     */
    ResultCode Version(std::string& version);
    /**
     * @brief 执行一次计算
     *
     * @param req 输入
     * @param rsp 输出
     * @return ResultCode
     */
    ResultCode Run(const Request& req, Response& rsp);

   private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};
}  // namespace blob
}  // namespace smartmore

#endif
