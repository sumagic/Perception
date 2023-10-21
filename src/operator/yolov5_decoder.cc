#include "operator/yolov5_decoder.h"

namespace perception {

Status Yolov5Decoder::Init(const YAML::Node& config)
{
    m_anchors = config["anchors"].as<std::vector<float>>();
    m_numHeads = config["num_heads"].as<size_t>();
    m_numAnchors = m_anchors.size() / 2 / m_numHeads;
    m_strides = config["strides"].as<std::vector<size_t>>();
    m_numClasses = config["num_classes"].as<size_t>();
    return SUCCESS;
}

Status Yolov5Decoder::Decode(const std::vector<Tensor<float>>& preds,
    std::vector<PredBox>& bboxes)
{
    assert(preds.size() == m_numHeads);

    bboxes.clear();
    for(size_t i = 0; i < m_numHeads; ++i) {
        auto& pred = preds[i]; // 3 * 76 * 76 * 85
        size_t& stride = m_strides[i];
        auto& dims = pred.dimensions();
        size_t num_anchors = dims[0];
        size_t gridH = dims[1];
        size_t gridW = dims[2];
        size_t vec = dims[3];

        assert(m_numClasses == (vec - 5));
        assert(num_anchors == m_numAnchors);

        for (size_t j = 0; j < m_numAnchors; ++j) {
            for (size_t h = 0; h < gridH; ++h) {
                for (size_t w = 0; w < gridW; ++w) {
                    
                }
            }
        }

    }
    return SUCCESS;
}
} // namespace perception