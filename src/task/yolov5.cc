#include "task/yolov5.h"

namespace perception
{
Status Yolov5::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status Yolov5::Process(const cv::Mat& image, std::vector<PredBox>& object_infos)
{
    return SUCCESS;
}
} // namespace perception