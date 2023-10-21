#ifndef __PERCEPTION_BOX_H__
#define __PERCEPTION_BOX_H__

#include "common.h"

namespace perception {

struct Box {
    size_t cx;
    size_t cy;
    size_t width;
    size_t height;

    Box(const size_t icx, const size_t icy, const size_t iwidth, const size_t iheight): cx(icx), cy(icy), width(iwidth), height(iheight) {}
    Box(const Box& box): cx(box.cx), cy(box.cy), width(box.width), height(box.height) {}
}; // namespace Box

struct PredBox {
    float score;
    size_t id;
    Box box;
    PredBox(const Box& ibox, const float iscore, const size_t iid): box(ibox), score(iscore), id(iid) {}
}; // struct PredBox

} // namespace perception
#endif // __PERCEPTION_BOX_H__