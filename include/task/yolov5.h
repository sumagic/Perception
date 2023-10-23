#ifndef __PERCEPTION_YOLOV5_H__
#define __PERCEPTION_YOLOV5_H__

#include "yaml-cpp/yaml.h"
#include "common.h"

namespace perception
{

class Yolov5
{
public:
    Yolov5();
    ~Yolov5();
    bool Init(const YAML::Node& yaml_node);
}; // class Yolov5
} // namespace perception

#endif // __PERCEPTION_YOLOV5_H__