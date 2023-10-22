#include "operator/letter_box.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN
namespace perception
{

Status LetterBox::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status LetterBox::Run(std::vector<Tensor<uint8_t>>& ins,
        std::vector<Tensor<uint8_t>>& outs)
{
    for (size_t i = 0; i < outs.size(); i++) {
        auto& idims = ins[i].dimensions(); // DHWC, input images
        auto& odims = outs[i].dimensions(); // DHWC, output images

        float hscale = (float)odims[1] / idims[1]; // targetH / inputH
        float wscale = (float)odims[2] / idims[2]; // targetW / inputW
        float scale = hscale > wscale ? wscale : hscale;
        size_t rh = (size_t)(idims[1] * scale);
        size_t rw = (size_t)(idims[2] * scale);

        auto& in = ins[i];
    #ifdef USE_NCNN
        ncnn::Mat tmp = ncnn::Mat::from_pixels_resize((const unsigned char*)in.data(), ncnn::Mat::PIXEL_BGR2RGB, idims[2], idims[1], rw, rh);
        ncnn::Mat in_pad(odims[2], odims[1], odims[3], sizeof(float));
        size_t hpad = odims[1] - idims[1];
        size_t wpad = odims[2] - idims[2];
        ncnn::copy_make_border(tmp, in_pad, hpad / 2, hpad - hpad / 2, wpad / 2, wpad - wpad / 2, ncnn::BORDER_CONSTANT, 114.f);
    #endif // USE_NCNN
    }
    return SUCCESS;
}

} // namespace perception