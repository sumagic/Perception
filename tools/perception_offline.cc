#include "common.h"
#include "config.h"
#include "utils/file.h"

#include "opencv2/opencv.hpp"

#include <string>
#include <vector>
#include <fstream>


int main(int argc, char **argv)
{
    LOG_INFO("start to process image: ");

    std::string yaml_file_path = "config/perception_offline.yaml";
    if(!perception::IsFileExist(yaml_file_path)) {
        LOG_ERROR("yaml file: %s is not exist", yaml_file_path.c_str());
        return -1;
    }

    YAML::Node config = YAML::LoadFile(yaml_file_path);
    std::string image_source_dir = config["image_source_dir"].as<std::string>();
    if (!perception::IsFileExist(image_source_dir)) {
        LOG_ERROR("image source dir: %s is not exist", image_source_dir.c_str());
        return -1;
    }

    std::vector<std::string> src_image_list = {};
    cv::glob(image_source_dir, src_image_list, false);
    for (auto &src_image : src_image_list) {
        LOG_INFO("start to process image: %s", src_image.c_str());
    }
    return 0;
}