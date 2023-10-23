#ifndef __PERCEPTION_YOLOV5_H__
#define __PERCEPTION_YOLOV5_H__

#include "yaml-cpp/yaml.h"
#include "common.h"
#include "utils/box.h"
#include "ai_engine/ncnn_engine.h"
#include "operator/letter_box.h"
#include "operator/sub_mean_scale.h"
#include "operator/yolov5_decoder.h"
#include "operator/predbox_nms.h"

#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif // USE_OPENCV

#include <vector>
#include <string>

namespace perception
{

class Yolov5
{
public:
    Yolov5() {}
    ~Yolov5() {}
    Status Init(const YAML::Node& yaml_node);
    Status Process(const cv::Mat& image, std::vector<PredBox>& object_infos);

private:
    LetterBox m_letterBox;
    SubMeanScale m_subMeanScale;
    NCNNEngine m_engine;
    Yolov5Decoder m_decoder;
    PredBoxNMS m_predBoxNMS;
}; // class Yolov5
} // namespace perception

#endif // __PERCEPTION_YOLOV5_H__