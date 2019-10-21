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
 * @file HumanDetector.cpp
 * @brief HumanDetector class definition.
 *
 * @date 10/20/2019
 */

#include <HumanDetector.hpp>

HumanDetector::HumanDetector() {
	conf_threshold = 0.6;  // Confidence threshold
	nms_threshold = 0.4;  // Non-maximum suppression threshold
	inpWidth = 416;  // Width of network's input image
	inpHeight = 416;  // Height of network's input image

	config_file_path = "../models/yolov3.cfg";  // Add path to the config file
	weight_file_path = "../models/yolov3.weights";  //Add path to the weight file

	//  Store class labels in the session memory
	class_labels_file_path = "../models/class.labels";
	std::ifstream ifs(class_labels_file_path.c_str());
	std::string line;
	while (ifs >> line) {
		class_labels.push_back(line);
	}
	net = cv::dnn::readNetFromDarknet(config_file_path, weight_file_path);
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

HumanDetector::~HumanDetector() {}

std::vector<cv::Rect> HumanDetector::predict(cv::Mat frame) {
	if (frame.empty()) {
		std::cout << "Error reading frame!!!" << std::endl;
	}
	cv::Mat blob;
	cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(inpWidth, inpHeight),\
											 cv::Scalar(0,0,0), true, false);
	net.setInput(blob);
	std::vector<cv::Mat> preds;
	net.forward(preds, getOutputsNames(net));
	std::vector<int> class_ids;
	std::vector<float> confidences;
	std::vector<int> indices;
	postProcess(frame, preds, class_ids, confidences, indices);
	return prediction_boxes;
}

std::vector<cv::String> HumanDetector::getOutputsNames(const cv::dnn::Net& net) {
	static std::vector<cv::String> labels;
	if (labels.empty()) {
		std::vector<int> out_layers = net.getUnconnectedOutLayers();
		std::vector<cv::String> layer_names = net.getLayerNames();
		labels.resize(out_layers.size());
		for (size_t i = 0; i < out_layers.size(); ++i) {
			labels[i] = layer_names[out_layers[i] - 1];
		}
	}
	std::cout<<labels.size()<<std::endl;
	return labels;
}

void HumanDetector::postProcess(cv::Mat& frame, const std::vector<cv::Mat>& preds, \
					std::vector<int> class_ids, std::vector<float> confidences,\
													 std::vector<int> indices) {
	for (size_t i = 0; i < preds.size(); ++i) {
		float* data = (float*)preds[i].data;
		for (int j = 0; j < preds[i].rows; ++j, data += preds[i].cols) {
			cv::Mat scores = preds[i].row(j).colRange(5, preds[i].cols);
			cv::Point class_id_point;
			double confidence;
			// Get the value and location of the maximum score
			cv::minMaxLoc(scores, 0, &confidence, 0, &class_id_point);
			if (confidence > conf_threshold) {
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;
				if(class_id_point.x == 0){
				class_ids.push_back(class_id_point.x);
				confidences.push_back((float)confidence);
				prediction_boxes.push_back(cv::Rect(left, top, width, height));
				}
			}
		}
	}
	cv::dnn::NMSBoxes(prediction_boxes, confidences, conf_threshold, nms_threshold,\
																		 indices);
	for (size_t i = 0; i < indices.size(); ++i) {
		int idx = indices[i];
		cv::Rect box = prediction_boxes[idx];
		std::cout << "Box " << idx << ":" <<  box.x << " " << box.y << " " << box.x \
								+ box.width << " " << box.y + box.height << std::endl;
	
	}
}
