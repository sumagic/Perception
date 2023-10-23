#include "operator/predbox_nms.h"

namespace perception
{
Status PredBoxNMS::Init(const YAML::Node& config)
{
    return SUCCESS;
}

Status PredBoxNMS::Run(const std::vector<PredBox>& ins,
        std::vector<PredBox>& outs)
{
    size_t count = ins.size();
    std::vector<int> index(count);
    for (size_t i = 0; i < count; i++) index[i] = i;

    // 按照score从大到小冒泡排序
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            if (ins[i].score < ins[j].score) {
                size_t tmp = index[i];
                index[i] = index[j];
                index[j] = tmp;
            }
        }
    }

    outs.clear();
    // nms
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            auto& left = index[i];
            // 被舍弃掉的框
            if (left < 0) continue;
            auto& right = index[j];
            if (right < 0) continue;

            float iou = PredBoxIoU(ins[left], ins[right]);
            if (iou > m_maxIoU) {
                index[j] = -1;
                continue;
            }
            outs.push_back(ins[right]);
        }
    }

    return SUCCESS;
}
} // namespace perception