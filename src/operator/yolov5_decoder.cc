#include "operator/yolov5_decoder.h"

namespace perception {

Status Yolov5Decoder::Init(const YAML::Node& config)
{
    m_anchors = config["anchors"].as<std::vector<float>>();
    m_numHeads = config["num_heads"].as<size_t>();
    m_strides = config["strides"].as<std::vector<size_t>>();
    return SUCCESS;
}

Status Yolov5Decoder::Decode(const std::vector<Tensor<float>>& preds,
    std::vector<std::vector<PredBox>>& bboxes)
{
    assert(preds.size() == m_numHeads);
    for(size_t i = 0; i < m_numHeads; ++i) {
        auto& pred = preds[i];
        size_t stride = m_strides[i];
        

    }
    return SUCCESS;
}
} // namespace perception