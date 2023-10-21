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
    NCNNEngine(const YAML::Node& config);
    ~NCNNEngine();

    Status Init();
    Status Run(const std::vector<Tensor<InputDType>>& input, std::vector<Tensor<OutputDType>>& output);
    Status Release();

private:
    ncnn::Net m_net;
};
} // namespace perception

#endif // __PERCEPTION_NCNN_H__