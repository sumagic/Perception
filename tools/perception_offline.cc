#include "common.h"
#include "config.h"

#include <string>
#include <vector>

int main(int argc, char **argv)
{
    LOG_INFO("start to process image: ");

    YAML::Node config = YAML::LoadFile("config/perception_offline.yaml");
    std::vector<std::string> src_image_list = config["image_source_dir"].as<std::vector<std::string>>();
    for (auto &src_image : src_image_list) {
        LOG_INFO("start to process image: %s", src_image.c_str());
    }
    return 0;
}