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
 * @file Scene.hpp
 * @brief Scene class definition.
 *
 * @date 10/20/2019
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
	cv::Mat imgL;
	cv::Mat imgR;
	Stereo stereo_obj;
	double camera_focal_length;
    double camera_baseline;
    double camera_f_x_camera_B;
    double camera_center_x;
    double camera_center_y;

	HumanDetector human_detector_obj;
	std::vector<std::pair<cv::Rect, cv::Point3d>> locations;
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
	 * @return none
	 */
	void locateObstacle(cv::Mat imgL, cv::Mat imgR, bool visualize);

	/**
	 * @brief A function to return the details of the obstacles detected in the frame.
	 * @param std::vector<cv::Rect> Prediction boxes of human obstacles.
	 * @param cv::Mat Disparity image between the right and left images.
	 * @return std::vector<std::pair<cv::Rect, cv::Point3d>> A vector containing pair
	 * of the obstacle location and their bounding boxes.
	 */
	std::vector<std::pair<cv::Rect, cv::Point3d>>  getObstacleInformation(\
		std::vector<cv::Rect> prediction_boxes, cv::Mat &disparity_image);
	
	/**
	 * @brief A function to draw the rectangular bounding boxes on 
	 * the image with their position in the scene.
	 * @param cv::Rect Bounding box value of the label
	 * @param cv::Point3d The coordinate details of the obstacle
	 * @param cv::Mat The left image on which thebounding boxes ave to be drawn
	 * @return none
	 */
	void drawPred(cv::Rect bounding_box, cv::Point3d coords, cv::Mat &frame);
};

#endif  // INCLUDE_SCENE_HPP_
