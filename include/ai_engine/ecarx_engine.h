#ifndef __PERCEPTION_ECAR_ENGINE_H__
#define __PERCEPTION_ECAR_ENGINE_H__

#include "common.h"
#include "utils/tensor.h"

#include <yaml-cpp/yaml.h>

namespace perception {

class ECarXEngine
{
public:
    ECarXEngine() {}
    ~ECarXEngine() {}
    Status Init(const YAML::Node& config);
    Status Run(const std::vector<Tensor<float>>& ins, std::vector<Tensor<float>>& outs);

private:
    uint32_t m_ctx;
    std::string m_modelFile;
    
}; // class ECarXEngine
} // namespace perception

#endif // __PERCEPTION_ECARX_ENGINE_H__