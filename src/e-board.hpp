#pragma once
#ifndef E_BOARD_HPP
#define E_BOARD_HPP
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <vector>

namespace eboard {
	void drawCircles(int evt, int x, int y, int flags, void* param);
	std::vector<cv::Point2f> getPoints(cv::Mat input);
	cv::Mat warpPerspective(const std::vector<cv::Point2f>& points, cv::Mat input);
	std::vector<cv::Point2f> getSquares(cv::Mat& input);
	void detectMovement(cv::Mat& input);
}

#endif //E_BOARD_HPP
