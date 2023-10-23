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

Status LetterBox::Run(const Image& in, Image& out)
{
    auto& idims = in.dimensions(); // DHWC, input images
    auto& odims = out.dimensions(); // DHWC, output images

    float hscale = (float)odims[0] / idims[0]; // targetH / inputH
    float wscale = (float)odims[1] / idims[1]; // targetW / inputW
    m_scale = hscale > wscale ? wscale : hscale;
    size_t rh = (size_t)(idims[0] * m_scale);
    size_t rw = (size_t)(idims[1] * m_scale);

    #ifdef USE_NCNN
        ncnn::Mat tmp = ncnn::Mat::from_pixels_resize((const unsigned char*)in.data(), ncnn::Mat::PIXEL_BGR2RGB, idims[1], idims[0], rw, rh);
        ncnn::Mat in_pad(odims[1], odims[0], odims[2], sizeof(float));
        m_hPad = odims[0] - idims[0];
        m_wPad = odims[1] - idims[1];
        ncnn::copy_make_border(tmp, in_pad, m_hPad / 2, m_hPad - m_hPad / 2, m_wPad / 2, m_wPad - m_wPad / 2, ncnn::BORDER_CONSTANT, 114.f);
    #endif // USE_NCNN

    return SUCCESS;
}

void LetterBox::Restore(std::vector<PredBox>& predboxes)
{

}

} // namespace perception