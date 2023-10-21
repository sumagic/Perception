#include "operator/sub_mean_scale.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN

namespace perception {
Status SubMeanScale::Init(const YAML::Node& config)
{
    m_mean = config["mean"].as<std::vector<std::vector<float>>>();
    m_scale = config["scale"].as<std::vector<std::vector<float>>>();
    return SUCCESS;
}

Status SubMeanScale::Run(std::vector<Tensor<float>>& ins,
                         std::vector<Tensor<float>>& outs)
{
    assert(ins.size() == outs.size());
    for (size_t i = 0; i < outs.size(); i++) {
    
    #ifdef USE_NCNN
        auto& dims = outs[i].dimensions(); // DCHW
        ncnn::Mat tmp = ncnn::Mat(dims[3], dims[2], dims[0], dims[1], ins[i].data(), sizeof(float));
        tmp.substract_mean_normalize(m_mean[i].data(), m_scale[i].data());
    #endif

    }
    return SUCCESS;
}
} // namespace perception