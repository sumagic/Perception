#include "task/yolov5.h"

namespace perception
{
Status Yolov5::Init(const YAML::Node& config)
{
    Status status = m_letterBox.Init(config["letter_box"]);
    if (status != SUCCESS) {
        LOG_ERROR("letter box init failed, ret=%x", status);
        return status;
    }
    LOG_INFO("letter box init success");

    status = m_subMeanScale.Init(config["sub_mean_scale"]);
    if (status != SUCCESS) {
        LOG_ERROR("sub mean scale init failed, ret=%x", status);
        return status;
    }
    LOG_INFO("sub mean scale init success");

    status = m_engine.Init(config["engine"]);
    if (status != SUCCESS) {
        LOG_ERROR("engine init failed, ret=%x", status);
        return status;
    }
    LOG_INFO("engine init success");

    m_decoder.Init(config["decoder"]);
    if (status != SUCCESS)
    {
        LOG_ERROR("decoder init failed, ret=%x", status);
        return status;
    }
    LOG_INFO("decoder init success");

    m_predBoxNMS.Init(config["pred_box_nms"]);
    if (status != SUCCESS) {
        LOG_ERROR("pred box nms init failed, ret=%x", status);
        return status; 
    }
    LOG_INFO("pred box nms init success");

    LOG_INFO("task: Yolov5 init success");
    return SUCCESS;
}

Status Yolov5::Process(const cv::Mat& image, std::vector<PredBox>& object_infos)
{
    auto mapped = Eigen::TensorMap<Image>(image.data, 1, image.rows, image.cols, image.channels());
    Image eimage = Eigen::TensorMap<Image>(mapped);

    ImageFloat out;
    Status status = m_letterBox.Run(eimage, out);
    if (status != SUCCESS) {
        LOG_ERROR("letter box failed, ret=%x", status);
        return status;
    }

    status = m_subMeanScale.Run(out);
    if (status != SUCCESS) {
        LOG_ERROR("sub mean scale failed, ret=%x", status);
    }

    std::vector<ImageFloat> ins = {out};
    std::vector<Tensor<float>> outs = {};
    status = m_engine.Run<float, float>(ins, outs);
    if (status != SUCCESS) {
        LOG_ERROR("engine run failed, ret=%x", status);
        return status;
    }

    std::vector<PredBox> bboxes = {};
    status = m_decoder.Decode(outs, bboxes);
    if (status != SUCCESS) {
        LOG_ERROR("decode failed, ret=%x", status);
        return status;
    }

    object_infos.clear();
    status = m_predBoxNMS.Run(bboxes, object_infos);
    if (status != SUCCESS) {
        LOG_ERROR("pred box nms failed, ret=%x", status);
        return status;
    }

    return SUCCESS;
}
} // namespace perception