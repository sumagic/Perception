#include "ai_engine/ecarx_engine.h"

#include "ecarx_engine_api.h"

namespace perception{

Status ECarXEngine::Init(const YAML::Node& config) {
    return SUCCESS;
}

Status ECarXEngine::Run(const std::vector<Tensor<float>>& ins, std::vector<Tensor<float>>& outs)
{
    return SUCCESS;
}
} // namespace perception