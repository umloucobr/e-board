#include "e-board.hpp"

void eboard::drawCircles(int evt, int x, int y, int flags, void* param) {
	if (evt == cv::EVENT_LBUTTONDOWN) 
	{
		std::vector<cv::Point2f>* ptPtr = static_cast<std::vector<cv::Point2f>*>(param);
		ptPtr->push_back(cv::Point(x, y));
	}
}

std::vector<cv::Point2f> eboard::getPoints(cv::Mat input) {
	std::vector<cv::Point2f> points{};
	cv::namedWindow("setpoints", cv::WINDOW_AUTOSIZE);

	cv::setMouseCallback("setpoints", drawCircles, (void*)&points);

	//ESC.
	while (cv::waitKey(20) != 27)
	{
		cv::imshow("setpoints", input);

		if (points.size() == 1)
		{
			cv::circle(input, points[0], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 2)
		{
			cv::circle(input, points[1], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 3)
		{
			cv::circle(input, points[2], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 4)
		{
			cv::circle(input, points[3], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
			cv::destroyAllWindows();
			return points;
		}
	}
	cv::destroyAllWindows();
	std::cerr << "Not all points filled.";
	return points;
}

cv::Mat eboard::warpPerspective(const std::vector<cv::Point2f>& points, cv::Mat input) {
	cv::namedWindow("warpperspective", cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point2f> dstPoints {cv::Point(0,0), cv::Point(800, 0), cv::Point(0, 800), cv::Point(800, 800)};
	cv::Mat output;
	cv::Mat matrix {cv::getPerspectiveTransform(points, dstPoints)};

	//cv::resize(input, input, cv::Size(800, 800));
	cv::warpPerspective(input, output, matrix, cv::Size(1920, 1080));

	//ESC.
	while (cv::waitKey(20) != 27)
	{
		cv::imshow("warpperspective", output);
	}
	cv::destroyAllWindows();
	return output;
};

std::vector<cv::Point2f> eboard::getSquares(cv::Mat& input) {
	std::vector<cv::Point2f> corners{};

	bool patternFound {cv::findChessboardCorners(input, cv::Size(7,7), corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE+ cv::CALIB_CB_FAST_CHECK)};
	//cv::drawChessboardCorners(input, cv::Size(7,7), corners, patternFound);
	for (int i = 0; i < corners.size(); i++)
	{
		cv::Point point = corners[i];
		cv::circle(input, point, 3, cv::Scalar(0, 255, 0));
		cv::putText(input, std::to_string(i), point, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
	}

	return corners;
}

void eboard::detectMovement(cv::Mat& input) {
	
}