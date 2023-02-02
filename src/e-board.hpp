#pragma once
#ifndef E_BOARD_HPP
#define E_BOARD_HPP
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

namespace eboard {
	void drawCircles(int evt, int x, int y, int flags, void* param);
	std::vector<cv::Point2f> getPoints(cv::Mat image);
	cv::Mat warpPerspective(const std::vector<cv::Point2f>& points, cv::Mat& input);
}

#endif //E_BOARD_HPP
