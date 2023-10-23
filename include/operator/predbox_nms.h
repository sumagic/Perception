#ifndef __PERCEPTION_PREDBOX_NMS_H__
#define __PERCEPTION_PREDBOX_NMS_H__

#include "common.h"
#include "utils/tensor.h"
#include "utils/box.h"

#include <yaml-cpp/yaml.h>
#include <vector>

namespace perception {

class PredBoxNMS
{
public:
    PredBoxNMS() {}
    ~PredBoxNMS() {}

    Status Init(const YAML::Node& config);
    Status Run(std::vector<PredBox>& ins,
        std::vector<PredBox>& outs);

private:
}; // class ResizeBorder

} // namespace perception

#endif // __PERCEPTION_PREDBOX_NMS_H__