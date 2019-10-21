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
 * @file Scene.cpp
 * @brief Scene class implementation.
 *
 * @date 10/20/2019
 */

#include <Scene.hpp>

Scene::Scene() {
    camera_focal_length = 2262.52;
    camera_baseline = 0.209;
    camera_f_x_camera_B = camera_focal_length * camera_baseline;
    camera_center_x = 1096.98;
    camera_center_y = 513.137;
}

Scene::~Scene() {}

void Scene::locateObstacle(cv::Mat imgL, cv::Mat imgR, bool visualize) {
    std::vector<cv::Rect> prediction_boxes;
    prediction_boxes = human_detector_obj.predict(imgL);

    //  Compute disparity
    cv::Mat disparity_image;
    disparity_image = stereo_obj.getDisparity(imgL, imgR);

    /* Overlap the detections with the disparity image vector of pairs.
     * each pair consists of bounding boxes and 3D coordinates
     */
    std::vector<std::pair<cv::Rect, cv::Point3d>> location = getObstacleInformation(prediction_boxes, disparity_image);
    if (visualize == true) {
        cv::Mat visualization_frame = imgL.clone();
        for (auto obstacle_information: location) {
            drawPred(obstacle_information.first, obstacle_information.second,\
                                                         visualization_frame);
        }
        cv::imwrite("/home/sandeep/terpbotics_dummy/data/1_Disp.png", disparity_image);
        cv::imshow("Output", visualization_frame);
        cv::waitKey();
    }
}

std::vector<std::pair<cv::Rect, cv::Point3d>> Scene::getObstacleInformation(\
                std::vector<cv::Rect> prediction_boxes, cv::Mat &disparity_image) {
    //  Loop through the detections
    for (auto prediction_box: prediction_boxes) {
        // Select only the region of interest from the bounding box
        cv::Rect roi(prediction_box);
        roi.x += 0.35 * roi.width;
        roi.y += 0.35 * roi.height;
        roi.width = 0.3 * roi.width;
        roi.height = 0.3 * roi.height;
        cv::Mat obstacle_disparity = disparity_image(roi);

        //  Compute average disparity
        float obstacle_mean_disparity = 0;
        int disp_pixel_count = 0;
        for (int r = 0; r < obstacle_disparity.rows; ++r) {
            for (int c = 0; c < obstacle_disparity.cols; ++c) {
                if (obstacle_disparity.at<float>(r, c) <= 0) {
                    continue;
                }
                obstacle_mean_disparity += obstacle_disparity.at<float>(r, c);
                ++disp_pixel_count;
            }
        }

        if (disp_pixel_count > 0) {
            obstacle_mean_disparity /= float(disp_pixel_count);

            if (obstacle_mean_disparity > 0) {
                //  Compute X, Y, Z for the bounding box
                double X, Y;
                double Z = camera_f_x_camera_B / (double)obstacle_mean_disparity;

                /*  Use the x coordinate of bottom left, bottom right, or inside of the bounding 
                box depending on where the obstacle is in the scene.
                */
                X = (((prediction_box.x + prediction_box.width / 2) - camera_center_x) * Z) / camera_focal_length;
                Y = ((prediction_box.y + prediction_box.height - camera_center_y) * Z) / camera_focal_length;
                
                //  Append X, Y, Z, tgainst each bounding box.
                std::pair<cv::Rect, cv::Point3d> obstacle_information;
                obstacle_information.first = prediction_box;
                obstacle_information.second = cv::Point3d(X, Y, Z);
                locations.emplace_back(obstacle_information);
            }
        }
    }

    return locations;
}

void Scene::drawPred(cv::Rect bounding_box, cv::Point3d coords, cv::Mat &frame) {
    //Draw a rectangle displaying the bounding box
    cv::rectangle(frame, bounding_box, cv::Scalar(255, 178, 50), 3);
    std::stringstream stream;
    stream << std::setprecision(2) << coords.x << ", " << coords.y << ", " << coords.z;
    std::string coordinates_3D = stream.str();
    
    /*
    Get the label for the class name and its confidence
    Display the label at the top of the bounding box
    */
    int base_line;
    cv::Size label_size = cv::getTextSize(coordinates_3D, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &base_line);
    int top = std::max(bounding_box.y, label_size.height);
    cv::rectangle(frame, cv::Point(bounding_box.x, top - round(1.5*label_size.height)),\
         cv::Point(bounding_box.x + round(1.5*label_size.width), top + base_line), \
                                            cv::Scalar(255, 255, 255), cv::FILLED);
    cv::putText(frame, coordinates_3D, cv::Point(bounding_box.x, top), cv::FONT_HERSHEY_SIMPLEX,\
                                                                     0.75, cv::Scalar(0,0,0),1);
    std::cout << coordinates_3D << std::endl;
}
