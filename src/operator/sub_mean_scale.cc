#include "operator/sub_mean_scale.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN

namespace perception {
Status SubMeanScale::Init(const YAML::Node& config)
{
    m_mean = config["mean"].as<std::vector<float>>();
    m_scale = config["scale"].as<std::vector<float>>();
    return SUCCESS;
}

Status SubMeanScale::Run(ImageFloat& image)
{
    #ifdef USE_NCNN
        auto& dims = image.dimensions(); // DHWC
        ncnn::Mat tmp = ncnn::Mat(dims[2], dims[1], dims[3], image.data(), sizeof(float));
        tmp.substract_mean_normalize(m_mean.data(), m_scale.data());
    #endif

    return SUCCESS;
}
} // namespace perception