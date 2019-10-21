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
 * @file Stereo.cpp
 * @brief Stereo class implementation.
 *
 * @date 10/20/2019
 */

#include <Stereo.hpp>

Stereo::Stereo() {
    int num_disparities = 64;
    int block_size = 15;
	bm = cv::StereoBM::create(num_disparities, block_size);
    // bm->setROI1(roi1);
    // bm->setROI2(roi2);
    bm->setPreFilterCap(31);
    bm->setPreFilterSize(9);
    // blockSize: 15
    // bm->setBlockSize(15);
    bm->setMinDisparity(0);
    bm->setNumDisparities(128);
    bm->setTextureThreshold(0);
    bm->setUniquenessRatio(1);
    bm->setSpeckleWindowSize(250);
    bm->setSpeckleRange(10);
    bm->setDisp12MaxDiff(1);
/*=======
	bm = cv::StereoBM::create(16,5);
    bm -> setPreFilterCap(31);
    bm -> setBlockSize(5);
    bm -> setMinDisparity(0);
    bm -> setTextureThreshold(10);
    bm -> setUniquenessRatio(15);
    bm -> setSpeckleWindowSize(100);
    bm -> setSpeckleRange(32);
    bm -> setDisp12MaxDiff(1);
*/
}

Stereo::~Stereo() {}

cv::Mat Stereo::getDisparity(cv::Mat img_l, cv::Mat img_r) {
    cv::Mat img_l_gray, img_r_gray;
	cv::cvtColor(img_l, img_l_gray, cv::COLOR_BGR2GRAY);
	img_l_gray.convertTo(img_l_gray, CV_8U);
	cv::cvtColor(img_r, img_r_gray, cv::COLOR_BGR2GRAY);
	img_r_gray.convertTo(img_r_gray, CV_8U);

    cv::Mat disparity;
    bm->compute(img_l_gray, img_r_gray, disparity);

    disparity.convertTo(disparity, CV_32F, 1.0/16.0);

    // cv::Mat disparity = cv::Mat::zeros(100, 100, 1);  //  Random stub values.
    return disparity;
}
