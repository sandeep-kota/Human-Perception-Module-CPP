/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file Stereo.hpp
 * @brief Stereo class definition.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#ifndef INCLUDE_STEREO_HPP_
#define INCLUDE_STEREO_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief Stereo class for disparity calculation.
 */	
class Stereo {
 private:
    cv::Ptr<StereoBM> bm;
    double camera_focal_length;
    double camera_baseline;

 public:
    /**
     * @brief A constructor for Stereo class.
     * @param None
     * @return None
     */
    Stereo();

    /**
     * @brief A destructor for Stereo class.
     * @param None
     * @return None
     */
    ~Stereo();

    /**
     * @brief A function to calculate the disparity 
     * between the two images.
     * @param cv::Mat Left image
     * @param cv::Mat Right image
     * @return cv::Mat Disparity map
     */
    cv::Mat getDisparity(cv::Mat imgL, cv::imgR);
};

#endif  // INCLUDE_STEREO_HPP_
