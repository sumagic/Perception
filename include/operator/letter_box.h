#ifndef __PERCEPTION_RESIZE_BORDER_H__
#define __PERCEPTION_RESIZE_BORDER_H__

#include "common.h"
#include "utils/tensor.h"
#include "utils/box.h"

#include "yaml-cpp/yaml.h"

namespace perception
{
/**
 * NHWC
*/
class LetterBox
{
public:
    LetterBox() {}
    ~LetterBox() {}

    Status Init(const YAML::Node& config);
    Status Run(const Image& in, ImageFloat& out);
    void Restore(std::vector<PredBox>& prebox);

private:
    float m_scale;
    size_t m_hPad;
    size_t m_wPad;
    size_t m_srcWidth;
    size_t m_srcHeight;
    float m_padValue;
}; // class ResizeBorder

} // namespace perception

#endif // __PERCEPTION_RESIZE_BORDER_H__