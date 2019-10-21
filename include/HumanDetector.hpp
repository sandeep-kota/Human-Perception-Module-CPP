/**
 * @copyright BSD 3-Clause License 
 * Copyright (c) 2019, @author Sandeep Kota Sai Pavan
 * Copyright (c) 2019, @author Satyarth Praveen
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file HumanDetector.hpp
 * @brief HumanDetector class definition.
 *
 * @date 10/20/2019
 */

#ifndef INCLUDE_HUMANDETECTOR_HPP_
#define INCLUDE_HUMANDETECTOR_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

/**
 * @brief Human detector class contains the path to the 
 * YOLO_v3 model config file, weight file as private members.
 * Also has a vector of bounding box coordinates for each 
 * predicted label of human obstacles.
 */     
class HumanDetector {
 private:
    float conf_threshold, nms_threshold;
    int inpWidth, inpHeight;
    std::string config_file_path;
    std::string weight_file_path;
    std::string class_labels_file_path;
    std::vector<std::string> class_labels;
    std::vector<cv::Rect> prediction_boxes;
    cv::dnn::Net net;

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
    * @brief A function that generates the bounding box labels
    * for the human labels in the predictions.
    * @param img of type cv::Mat which is an image of the scene,
    * @return std::vector<cv::Rect> Returns bounding boxes .
    */
    std::vector<cv::Rect> predict(cv::Mat frame);

    /**
    * @brief A function to get the string vector of the outputs
    * of the deep neural network
    * @param cv::dnn::Net The model file of the deep neural network,
    * @return std::vector<cv::String> Returns string vector of the output labels
    */
    std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);

    /**
    * @brief A function to perform non-max suppression of bounding boxes
    * with low confidence values.
    * @param cv::Mat Image instance of the scene
    * @param std::vector<cv::Mat> A vector of the matrix of the predicitons
    * @param std::vector<int> A vector of the class id's of the predictions
    * @param std::vector<float> A vector containing the confidnce values of the predicted outputs
    * @param std::vector<int> A vector of the indices 
    * @return std::vector<cv::String> Returns string vector of the output labels
    */
    void postProcess(cv::Mat& frame, const std::vector<cv::Mat>& preds, std::vector<int> class_ids, std::vector<float> confidences, std::vector<int> indices);
};

#endif  // INCLUDE_HUMANDETECTOR_HPP_
