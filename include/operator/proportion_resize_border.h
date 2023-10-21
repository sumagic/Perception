#ifndef __PERCEPTION_RESIZE_BORDER_H__
#define __PERCEPTION_RESIZE_BORDER_H__

#include "common.h"
#include "utils/tensor.h"


#include "yaml-cpp/yaml.h"

namespace perception
{

class ProportionResizeBorder
{
public:
    ProportionResizeBorder() {}
    ~ProportionResizeBorder() {}

    Status Init(const YAML::Node& config);
    Status Run(std::vector<Tensor<float>>& ins,
        std::vector<Tensor<float>>& outs);
}; // class ResizeBorder

} // namespace perception

#endif // __PERCEPTION_RESIZE_BORDER_H__