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
#include <array>
#include <iterator>

namespace eboard {
	void drawCircles(int evt, int x, int y, int flags, void* param);
	std::vector<cv::Point2f> getPoints(cv::Mat input);
	cv::Mat warpPerspective(const std::vector<cv::Point2f>& points, cv::Mat input);
	std::vector<cv::Point2f> getCorners(cv::Mat& input);
	cv::Point2f findOuterCorners(const cv::Point2f& point1, const cv::Point2f& point2);	
	void drawCorners(cv::Mat& input, std::vector<cv::Point2f>& lines);
	void detectMovement(cv::Mat& input, std::vector<cv::Rect>& rectList);
}

#endif //E_BOARD_HPP
