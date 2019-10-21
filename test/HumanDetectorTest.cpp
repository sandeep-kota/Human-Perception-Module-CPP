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
 * @file HumanDetectorTest.cpp
 * @brief HumanDetector Test Cases.
 *
 * @date 10/20/2019
 */

#include <gtest/gtest.h>
#include <HumanDetector.hpp>
#include <Stereo.hpp>
#include <Scene.hpp>

TEST(HumanDetectorTest, numberOfDetectionsTest) {
	cv::Mat frame = cv::imread("../test/1_l.png", cv::IMREAD_COLOR);
	std::vector<cv::Rect> prediction_boxes;

	HumanDetector hd_obj;
	prediction_boxes = hd_obj.predict(frame);

	EXPECT_GT(int(prediction_boxes.size()), 1);
}

TEST(HumanDetectorTest, validDetectionBoxesTest) {
	cv::Mat frame = cv::imread("../test/1_l.png", cv::IMREAD_COLOR);
	std::vector<cv::Rect> prediction_boxes;

	HumanDetector hd_obj;
	prediction_boxes = hd_obj.predict(frame);

	for (auto prediction_box : prediction_boxes) {
		EXPECT_GE(prediction_box.x, 0);
		EXPECT_GE(prediction_box.y, 0);
		EXPECT_GT(prediction_box.width, 0);
		EXPECT_GT(prediction_box.height, 0);
	}
}