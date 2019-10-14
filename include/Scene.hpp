/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file Scene.hpp
 * @brief Stereo class definition.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#ifndef INCLUDE_SCENE_HPP_
#define INCLUDE_SCENE_HPP_

#include <iostream>
#include <vector>
#include <Stereo.hpp>
#include <HumanDetector.hpp>
#include <opencv2/opencv.hpp>


/**
 * @brief Scene class for stereo integration
 * with object detection predictions.
 */ 
class Scene {
 private:
    cv::Mat imgl;
    cv::Mat imgR;
    Stereo ster;
    HumanDetector hd;
    std::vector<std::vector<float>> distance;

 public:
    /**
     * @brief A constructor for Scene class.
     * @param None
     * @return None
     */
    Scene();

    /**
     * @brief A destructor for Scene class.
     * @param None
     * @return None
     */
    ~Scene();

    /**
     * @brief A function to locate obstacles in scene
     * w.r.t sensor frame.
     * @param cv::Mat Left image
     * @param cv::Mat Right image
     * @return std::vector<std::vector<float>> Coordinates
     * of obstacles w.r.t to sensor frame.
     */
    std::vector<std::vector<float>> locateObstacle(cv::Mat imgL, cv::imgR);
};

#endif  // INCLUDE_SCENE_HPP_
