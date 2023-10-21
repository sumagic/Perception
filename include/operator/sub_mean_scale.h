#ifndef __PERCEPTION_SUB_MEAN_SCALE_H__
#define __PERCEPTION_SUB_MEAN_SCALE_H__

#include "yaml-cpp/yaml.h"
#include "common.h"
#include "utils/tensor.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN

#include <vector>

namespace perception {

class SubMeanScale {
public:
SubMeanScale() {}
~SubMeanScale() {}

Status Init(const YAML::Node& node);
Status Run(std::vector<Tensor<float>>& ins,
    std::vector<Tensor<float>>& outs);

private:
    std::vector<std::vector<float>> m_mean;
    std::vector<std::vector<float>> m_scale;
#ifdef USE_NCNN
    ::ncnn::Mat m_mat;
#endif // USE_NCNN
}; // class SubMeanScale

} // namespace 


#endif // __PERCEPTION_SUB_MEAN_SCALE_H__