#include "operator/yolov5_decoder.h"

namespace perception {

Status Yolov5Decoder::Init(const YAML::Node& config)
{
    m_anchors = config["anchors"].as<std::vector<float>>();
    return SUCCESS;
}

Status Yolov5Decoder::Decode(const std::vector<Tensor<float>>& pred, std::vector<std::vector<PredBox>>& bboxes)
{
    assert(pred.size() == (m_anchors.size() / 2));
    return SUCCESS;
}
} // namespace perception