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
 * @file StereoTest.cpp
 * @brief Stereo Test Cases.
 *
 * @date 10/20/2019
 */

#include <gtest/gtest.h>
#include <Stereo.hpp>

TEST(StereoTest, disparityTest) {
	// Reading left and right stereo frame along with the ground truth disparity image
	cv::Mat frame_l = cv::imread("../test/1_l.png", cv::IMREAD_COLOR);
	cv::Mat frame_r = cv::imread("../test/1_r.png", cv::IMREAD_COLOR);
	cv::Mat frame_d = cv::imread("../test/1_d.png", cv::IMREAD_GRAYSCALE);

	// Computing disparity
	Stereo st_obj;
	cv::Mat disparity_image = st_obj.getDisparity(frame_l, frame_r);

	// Setting all invalid disparity values to 0
	disparity_image.setTo(0, disparity_image < 0); 
	disparity_image.convertTo(disparity_image, CV_8UC1);
	
	// Masking the ground truth disparity values with computed disparity 
	cv::Mat masked_gt = frame_d & disparity_image;

	// Computing per pixel error in disparity estimation
	cv::Mat diff;
	cv::subtract(masked_gt, disparity_image, diff);

	// Computing average error margin in disparity estimation
	int mean_error = 0;
    int nonzero_pixel_count = diff.total();
    mean_error = cv::sum(diff)[0];
    if (nonzero_pixel_count > 0) {
	    mean_error = mean_error/nonzero_pixel_count;
		EXPECT_LE(mean_error, 3);
    }
}