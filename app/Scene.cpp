/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file Scene.cpp
 * @brief Stereo class implementation.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Scene.hpp>

Scene::Scene() {
camera_focal_length = 0;
camera_baseline = 0;
}

std::vector<std::vector<float>> locateObstacle(cv::Mat imgL, cv::imgR) {
std::vector<int> dist = [10.5, 5.5, 4.5];  //  Random stub values.
distance.emplace_back(dist);
return dist;
}