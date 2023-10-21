#include "operator/proportion_resize_border.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN
namespace perception
{

Status ImageProportionResizeBorder::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status ImageProportionResizeBorder::Run(std::vector<Tensor<float>>& ins,
        std::vector<Tensor<float>>& outs)
{
    for (size_t i = 0; i < outs.size(); i++) {
        auto& idims = ins[i].dimensions();
        auto& odims = outs[i].dimensions(); // DHWC

        float hscale = (float)odims[1] / idims[1];
        float wscale = (float)odims[2] / idims[2];
        float scale = hscale > wscale ? wscale : hscale;
        size_t rh = (size_t)(idims[1] * scale);
        size_t rw = (size_t)(idims[2] * scale);

        auto& in = ins[i];
    #ifdef USE_NCNN
        ncnn::Mat out = ncnn::Mat::from_pixels_resize(in.data(), ncnn::Mat::PIXEL_BGR2RGB, idims[2], idims[1], rw, rh);

    #endif // USE_NCNN

    }
    return SUCCESS;
}

} // namespace perception