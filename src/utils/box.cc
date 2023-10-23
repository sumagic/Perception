#include "utils/box.h"
#include <string>

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

Status PredBox::Draw(cv::Mat& image, const std::vector<std::string>& class_names) const
{
    #ifdef USE_OPENCV
    cv::rectangle(image, box, ::cv::Scalar(0, 255, 0), 2);

    std::string text = class_names[id] + ": " + std::to_string(score);
    int baseLine = 0;
    cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    cv::putText(image, text, cv::Point(box.x, box.y-10), cv::FONT_HERSHEY_PLAIN, 8, CV_RGB(255, 0, 0));//红色字体注释
    #endif // USE_OPENCV
    return SUCCESS;
}


} // namespace perception