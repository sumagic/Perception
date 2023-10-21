#ifndef __PERCEPTION_YOLOV5_DECODER_H__
#define __PERCEPTION_YOLOV5_DECODER_H__

#include "common.h"
#include "utils/tensor.h"
#include "utils/box.h"
#include "yaml-cpp/yaml.h"

#include <vector>

namespace perception
{
class Yolov5Decoder
{
public:
    Yolov5Decoder() = default;
    ~Yolov5Decoder() = default;
    Status Init(const YAML::Node& config);
    Status Decode(const std::vector<Tensor<float>>& pred, 
        std::vector<PredBox>& bboxes);

private:
    std::vector<float> m_anchors = {};
    size_t m_numHeads;
    size_t m_numClasses;
    size_t m_numAnchors;
    std::vector<size_t> m_strides;
    float m_confidence;
    float m_iouThreshold;
};
} // namespace perception

#endif // __PERCEPTION_YOLOV5_DECODER_H__