/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file HumanDetector.cpp
 * @brief HumanDetector class implementation.
 * It contains the function definition to compute the human
 * bounding box labels of humans label from the YOLO_v3 model.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <HumanDetector.hpp>

HumanDetector::HumanDetector() {
    config_file_path = "./";  //  Random stub values.
    weight_file_path = "./";  //  Random stub values.
}

std::vector<std::vector<int>> HumanDetector::predict(cv::Mat img) {
    std::vector<int> bounding_box = {30, 40, 70, 20};  //  Random stub values.
    pred_labels.emplace_back(bounding_box);
    return pred_labels;
}
