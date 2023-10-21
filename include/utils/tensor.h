#ifndef __PERCEPTION_TENSOR_H__
#define __PERCEPTION_TENSOR_H__

#include "unsupported/Eigen/CXX11/Tensor"

namespace perception
{

// nchw
template <typename T>
using Tensor = Eigen::Tensor<float, 4, Eigen::RowMajor>;
} // namespace perception

#endif // __PERCEPTION_TENSOR_H__