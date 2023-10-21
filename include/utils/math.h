#ifndef __PERCEPTION_MATH_H__
#define __PERCEPTION_MATH_H__

#include <math.h>

namespace perception {
static inline float sigmoid(float x)
{
    return static_cast<float>(1.f / (1.f + exp(-x)));
}
} // namespace perception
#endif // __PERCEPTION_MATH_H__