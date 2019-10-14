/**
 * @copyright Copyright (c) Sandeep Kota Sai Pavan
 * @copyright Copyright (c) Satyarth Praveen
 * @copyright 3-Clause BSD License
 *
 * @file HumanDetector.hpp
 * @brief HumanDetector class definition.
 *
 * It contains the function definition to compute the human
 * bounding box labels of humans label from the YOLO_v3 model.
 *
 * @author Sandeep Kota Sai Pavan
 * @author Satyarth Praveen
 * @date 10/14/2019
 */

#ifndef INCLUDE_HUMANDETECTOR_HPP_
#define INCLUDE_HUMANDETECTOR_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief Human detector class contains the path to the 
 * YOLO_v3 model config file, weight file as private members.
 * Also has a vector of bounding box coorddinates for each 
 * predicted label of human obstacles.
 */     
class HumanDetector {
 private:
    std::string config_file_path;
    std::string weight_file_path;
    std::vector<std::vector<int>> pred_labels;

 public:
    /**
    * @brief A constructor for HumanDetector class.
    * @param None
    * @return None
    */
    HumanDetector();

    /**
    * @brief A destructor for HumanDetector class.
    * @param None
    * @return None
    */
    ~HumanDetector();

    /**
    * @brief predict function generates the bounding box labels
    * for the human labels in the predictions.
    * @param img of type cv::Mat which is an image of the scene,
    * @return std::vector<std::vector<int>> returns a vector of 
    * bounding box co-ordinates.
    */
    std::vector<std::vector<int>> predict(cv::Mat img);
};

#endif  // INCLUDE_HUMANDETECTOR_HPP_
