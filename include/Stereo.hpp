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
 * @file Stereo.hpp
 * @brief Stereo class definition.
 *
 * @date 10/20/2019
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
    cv::Ptr<cv::StereoBM> bm;
    cv::Mat disparity_image;
    
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
    cv::Mat getDisparity(cv::Mat img_l, cv::Mat img_r);
};

#endif  // INCLUDE_STEREO_HPP_
