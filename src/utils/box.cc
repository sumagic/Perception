#include "utils/box.h"

namespace perception
{

float BoxIoU(const Box& box1, const Box& box2)
{
    float iou = 0.0;
#ifdef USE_OPENCV
    cv::Rect all = box1 | box2;
    cv::Rect inter = box1 & box2;
    iou = (float)(inter.area()) / (float)(all.area());
#endif
    return iou;
}

float PredBoxIoU(const PredBox& predbox1, const PredBox& predbox2)
{
    if (predbox1.id == predbox2.id)
        return BoxIoU(predbox1.box, predbox2.box);
    return 0.0;
}   
} // namespace perception