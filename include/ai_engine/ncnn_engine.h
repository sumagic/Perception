#ifndef __PERCEPTION_NCNN_H__
#define __PERCEPTION_NCNN_H__

#include "utils/tensor.h"

#include "ncnn/net.h"
#include "yaml-cpp/yaml.h"
#include "common.h"

#include <string>
#include <vector>

namespace perception
{

class NCNNEngine
{
public:
    NCNNEngine() {}
    ~NCNNEngine() {}

    Status Init(const YAML::Node& config)
    {
        m_net.load_param(config["param"].as<std::string>().c_str());
        m_net.load_model(config["model"].as<std::string>().c_str());
        m_iName = config["input"].as<std::vector<std::string>>();
        m_oName = config["output"].as<std::vector<std::string>>();
        m_extractor = m_net.create_extractor();
        return SUCCESS;
    }

    template <typename InputDType, typename OutputDType>
    Status Run(const std::vector<Tensor<InputDType>>& ins, std::vector<Tensor<OutputDType>>& outs)
    {
        assert(ins.size() == m_iName.size());
        assert(outs.size() == m_oName.size());

        for (size_t i = 0; i < ins.size(); i++)
            m_extractor.input(m_iName[i].c_str(), ins[i].data);

        
        for (size_t i = 0; i < outs.size(); i++) {
            auto& dims = outs[i].dimensions(); // DCHW
            ncnn::Mat mat(dims[3], dims[2], dims[0], dims[1], outs[i].data(), sizeof(OutputDType));
            m_extractor.extract(m_oName[0].c_str(), mat);
        }

        return SUCCESS;
    }
    Status Release();

private:
    ncnn::Net m_net;
    std::string m_param;
    std::string m_model;
    std::vector<std::string> m_iName;
    std::vector<std::string> m_oName;
    ncnn::Extractor m_extractor;
};
} // namespace perception

#endif // __PERCEPTION_NCNN_H__