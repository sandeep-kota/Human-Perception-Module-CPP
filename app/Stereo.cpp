/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file Stereo.cpp
 * @brief Stereo class implementation.It contains the function 
 * definitions to compute disparity for distance estimation.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Stereo.hpp>

Stereo::Stereo() {
cv::Ptr<StereoBM> bm;
double camera_focal_length = 0;  //  Random stub values.
double camera_baseline = 0;  //  Random stub values.
}

cv::Mat Stereo::getDisparity(cv::Mat imgL, cv::imgR) {
cv::Mat disparity = cv::Mat::zeros(100, 100);  //  Random stub values.
return disparity;
}
