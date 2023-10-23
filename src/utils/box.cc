#include "utils/box.h"

#ifdef USE_OPENCV
    #include <opencv2/opencv.hpp>
#endif // USE_OPENCV

namespace perception
{

float BoxIoU(const Box& box1, const Box& box2)
{
    float iou = 0.0;
#ifdef USE_OPENCV
    cv::Rect left(box1.cx - width / 2, box1.cy - height / 2, width, height);
    cv::Rect right(box2.cx - width / 2, box2.cy - height / 2, width, height);
    iou = (float)cv::intersectedArea(left, right) / (float)cv::unionArea(left, right);
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