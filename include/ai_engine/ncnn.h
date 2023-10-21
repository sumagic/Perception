#ifndef __PERCEPTION_NCNN_H__
#define __PERCEPTION_NCNN_H__

#include "utils/tensor.h"

#include "ncnn/net.h"
#include "yaml-cpp/yaml.h"
#include "common.h"


namespace perception
{

template <typename InputDType, typename OutputDType>
class NCNNEngine
{
public:
    NCNNEngine() {}
    ~NCNNEngine() {}

    Status Init(const YAML::Node& config)
    {
        m_net.load_param(config["param"].as<std::string>().c_str());
        m_net.load_model(config["model"].as<std::string>().c_str());
        return SUCCESS;
    }
    Status Run(const std::vector<Tensor<InputDType>>& input, std::vector<Tensor<OutputDType>>& output);
    Status Release();

private:
    ncnn::Net m_net;
    std::string m_param;
    std::string m_model;
};
} // namespace perception

#endif // __PERCEPTION_NCNN_H__