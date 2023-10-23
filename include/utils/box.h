#ifndef __PERCEPTION_BOX_H__
#define __PERCEPTION_BOX_H__

#include "common.h"

#ifdef USE_OPENCV
    #include <opencv2/opencv.hpp>
#endif // USE_OPENCV

namespace perception {

using Box = cv::Rect;

float BoxIoU(const Box& box1, const Box& box2);

struct PredBox {
    float score;
    size_t id;
    Box box;

    PredBox(): score(0.0f), id(0), box(0, 0, 0, 0) {}
    PredBox(const Box& ibox, const float iscore, const size_t iid): box(ibox), score(iscore), id(iid) {}
}; // struct PredBox

float PredBoxIoU(const PredBox& predbox1, const PredBox& predbox2);

} // namespace perception
#endif // __PERCEPTION_BOX_H__