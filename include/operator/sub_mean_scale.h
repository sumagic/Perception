#ifndef __PERCEPTION_SUB_MEAN_SCALE_H__
#define __PERCEPTION_SUB_MEAN_SCALE_H__

#include "yaml-cpp/yaml.h"
#include "common.h"
#include "utils/tensor.h"

#include <vector>

namespace perception {

class SubMeanScale {
public:
SubMeanScale() {}
~SubMeanScale() {}

Status Init(const YAML::Node& node);
Status Run(ImageFloat& image);

private:
    std::vector<float> m_mean;
    std::vector<float> m_scale;
}; // class SubMeanScale

} // namespace 


#endif // __PERCEPTION_SUB_MEAN_SCALE_H__