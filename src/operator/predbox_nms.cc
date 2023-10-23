#include "operator/predbox_nms.h"

namespace perception
{
Status PredBoxNMS::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status PredBoxNMS::Run(std::vector<PredBox>& ins,
        std::vector<PredBox>& outs)
{
    return SUCCESS;
}
} // namespace perception