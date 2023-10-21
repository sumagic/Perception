#include "operator/yolov5_decoder.h"
#include "utils/math.h"

#include <cfloat>

namespace perception {

Status Yolov5Decoder::Init(const YAML::Node& config)
{
    m_anchors = config["anchors"].as<std::vector<float>>();
    m_numHeads = config["num_heads"].as<size_t>();
    m_numAnchors = m_anchors.size() / 2 / m_numHeads;
    m_strides = config["strides"].as<std::vector<size_t>>();
    m_numClasses = config["num_classes"].as<size_t>();
    m_confidence = config["box_confidence"].as<float>();
    m_iouThreshold = config["box_iou_threshold"].as<float>();
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
        size_t feat_size = dims[3];
    
        assert(m_numClasses == (feat_size - 5));
        assert(num_anchors == m_numAnchors);

        for (size_t j = 0; j < m_numAnchors; ++j) {
            float anchor_w = m_anchors[i * m_numAnchors * 2 + j * 2];
            float anchor_h = m_anchors[i * m_numAnchors * 2 + j * 2 + 1];
            for (size_t h = 0; h < gridH; ++h) {
                for (size_t w = 0; w < gridW; ++w) {
                    const float* feat = pred.data() + ( w + h * gridW + j * gridW * gridH ) * feat_size;
                    float box_conf = sigmoid(feat[4]);
                    if (box_conf < m_confidence) continue;
                    // argmax
                    size_t class_index = 0;
                    float confidence = -FLT_MAX;
                    for (size_t k = 0; k < m_numClasses; ++k) {
                        if (feat[5 + k] > confidence) {
                            class_index = k;
                            confidence = feat[5 + k];
                        }
                    }
                    confidence = box_conf * sigmoid(confidence);
                    if (confidence < m_confidence) continue;

                    // decode
                    float dx = sigmoid(feat[0]);
                    float dy = sigmoid(feat[1]);
                    float dw = sigmoid(feat[2]);
                    float dh = sigmoid(feat[3]);

                    float pb_cx = (dx * 2.f - 0.5f + j) * stride;
                    float pb_cy = (dy * 2.f - 0.5f + i) * stride;

                    float pb_w = pow(dw * 2.f, 2) * anchor_w;
                    float pb_h = pow(dh * 2.f, 2) * anchor_h;

                    float x0 = pb_cx - pb_w * 0.5f;
                    float y0 = pb_cy - pb_h * 0.5f;
                    float x1 = pb_cx + pb_w * 0.5f;
                    float y1 = pb_cy + pb_h * 0.5f;

                    PredBox box;
                    box.box.cx = (x0 + x1) / 2.f;
                    box.box.cy = (y0 + y1) / 2.f;
                    box.box.width = (x1 - x0);
                    box.box.height = (y1 - y0);
                    box.id = class_index;
                    box.score = confidence;    
                    bboxes.push_back(box);
                }
            }
        }

    }
    return SUCCESS;
}
} // namespace perception

