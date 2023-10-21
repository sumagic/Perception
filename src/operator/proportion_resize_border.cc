#include "operator/proportion_resize_border.h"

namespace perception
{

Status ProportionResizeBorder::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status ProportionResizeBorder::Run(std::vector<Tensor<float>>& ins,
        std::vector<Tensor<float>>& outs)
{
    return SUCCESS;
}

} // namespace perception