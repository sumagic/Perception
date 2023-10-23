#include "operator/letter_box.h"

#ifdef USE_NCNN
    #include "ncnn/net.h"
#endif // USE_NCNN

#include <algorithm>

namespace perception
{

Status LetterBox::Init(const YAML::Node& config)
{
    m_padValue = config["pad_value"].as<float>();
    return SUCCESS;
}

Status LetterBox::Run(const Image& in, ImageFloat& out)
{
    auto& idims = in.dimensions(); // DHWC, input images
    auto& odims = out.dimensions(); // DHWC, output images

    m_srcWidth = idims[1];
    m_srcHeight = idims[0];

    float hscale = (float)odims[0] / idims[0]; // targetH / inputH
    float wscale = (float)odims[1] / idims[1]; // targetW / inputW
    m_scale = hscale > wscale ? wscale : hscale;
    size_t rh = (size_t)(idims[0] * m_scale);
    size_t rw = (size_t)(idims[1] * m_scale);

    #ifdef USE_NCNN
        // 这里resize之后，tmp已经是fp32的数据
        ncnn::Mat tmp = ncnn::Mat::from_pixels_resize((const unsigned char*)in.data(), ncnn::Mat::PIXEL_BGR2RGB, idims[1], idims[0], rw, rh);
        ncnn::Mat in_pad(odims[1], odims[0], odims[2], out.data(), sizeof(float));
        m_hPad = odims[0] - idims[0];
        m_wPad = odims[1] - idims[1];
        // pad
        ncnn::copy_make_border(tmp, in_pad, m_hPad / 2, m_hPad - m_hPad / 2, m_wPad / 2, m_wPad - m_wPad / 2, ncnn::BORDER_CONSTANT, m_padValue);
    #endif // USE_NCNN

    return SUCCESS;
}

void LetterBox::Restore(std::vector<PredBox>& predboxes)
{
    float x1, y1, x2, y2;
    for (auto& predbox : predboxes)
    {
        float x0 = (predbox.box.x - (m_wPad / 2)) / m_scale;
        float y0 = (predbox.box.y - (m_hPad / 2)) / m_scale;
        float x1 = (predbox.box.x + predbox.box.width - (m_wPad / 2)) / m_scale;
        float y1 = (predbox.box.y + predbox.box.height - (m_hPad / 2)) / m_scale;

        x0 = std::max(std::min(x0, (float)(m_srcWidth - 1)), 0.f);
        y0 = std::max(std::min(y0, (float)(m_srcHeight - 1)), 0.f);
        x1 = std::max(std::min(x1, (float)(m_srcWidth - 1)), 0.f);
        y1 = std::max(std::min(y1, (float)(m_srcHeight - 1)), 0.f);

        predbox.box.x = x0;
        predbox.box.y = y0;
        predbox.box.width = x1 - x0;
        predbox.box.height = y1 - y0;
    }
}

} // namespace perception