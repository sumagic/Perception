#include "common.h"
#include "config.h"
#include "utils/file.h"

#include "opencv2/opencv.hpp"

#include <string>
#include <vector>
#include <fstream>

#include "task/yolov5.h"
#include "common.h"
#include "utils/box.h"

int main(int argc, char **argv)
{
    LOG_INFO("start to process image: ");

    std::string yaml_file_path = "config/perception_offline.yaml";
    if(!perception::IsFileExist(yaml_file_path)) {
        LOG_ERROR("yaml file: %s is not exist", yaml_file_path.c_str());
        return -1;
    }

    YAML::Node config = YAML::LoadFile(yaml_file_path);
    std::string image_source_dir = config["ImageSourceDir"].as<std::string>();
    if (!perception::IsFileExist(image_source_dir)) {
        LOG_ERROR("image source dir: %s is not exist", image_source_dir.c_str());
        return -1;
    }
    std::string image_output_dir = config["ImageOutputDir"].as<std::string>();

    std::vector<std::string> class_names = config["class_names"].as<std::vector<std::string>>();

    std::vector<std::string> src_image_list = {};
    cv::glob(image_source_dir, src_image_list, false);

    perception::Yolov5 yolov5;
    perception::Status status = yolov5.Init(config);
    if (status != perception::SUCCESS) {
        LOG_ERROR("yolov5 init failed");
        return status;
    }
    
    std::vector<perception::PredBox> objects = {};
    for (auto &src_image : src_image_list) {
        LOG_INFO("start to process image: %s", src_image.c_str());

        cv::Mat image = cv::imread(src_image);
        status = yolov5.Process(image, objects);
        if (status != perception::SUCCESS) {
            LOG_ERROR("yolov5 detect failed");
            return status;
        }
        LOG_INFO("detect objects: %ld", objects.size());
        for (auto &obj : objects) {
            status = obj.Draw(image, class_names);
            if (status != perception::SUCCESS) {
                LOG_ERROR("obj draw failed");
                return status;
            }
        }
        cv::imwrite(image_output_dir + "/" + src_image, image);
    }
    return 0;
}