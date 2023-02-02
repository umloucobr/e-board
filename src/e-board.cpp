#include "e-board.hpp"

void eboard::drawCircles(int evt, int x, int y, int flags, void* param) {
	if (evt == cv::EVENT_LBUTTONDOWN) 
	{
		std::vector<cv::Point2f>* ptPtr = static_cast<std::vector<cv::Point2f>*>(param);
		ptPtr->push_back(cv::Point(x, y));
	}
}

std::vector<cv::Point2f> eboard::getPoints(cv::Mat image) {
	std::vector<cv::Point2f> points{};
	cv::namedWindow("setpoints", cv::WINDOW_AUTOSIZE);

	cv::setMouseCallback("setpoints", drawCircles, (void*)&points);

	//ESC.
	while (cv::waitKey(20) != 27)
	{
		cv::imshow("setpoints", image);

		if (points.size() == 1)
		{
			cv::circle(image, points[0], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 2)
		{
			cv::circle(image, points[1], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 3)
		{
			cv::circle(image, points[2], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
		}
		else if (points.size() == 4)
		{
			cv::circle(image, points[3], 5, cv::Scalar(255, 0, 0), cv::FILLED); //Blue circle.
			cv::destroyAllWindows();
			return points;
		}
	}
	cv::destroyAllWindows();
	std::cerr << "Not all points filled.";
	return points;
}

cv::Mat eboard::warpPerspective(const std::vector<cv::Point2f>& points, cv::Mat& input) {
	cv::namedWindow("warpperspective", cv::WINDOW_AUTOSIZE);

	std::vector<cv::Point2f> dstPoints {cv::Point(0,0), cv::Point(500, 0), cv::Point(0, 500), cv::Point(500, 500)};
	cv::Mat output;
	cv::Mat matrix {cv::getPerspectiveTransform(points, dstPoints)};

	cv::resize(input, input, cv::Size(500, 500));
	cv::warpPerspective(input, output, matrix, cv::Size(500, 500));

	//ESC.
	while (cv::waitKey(20) != 27)
	{
		cv::imshow("warpperspective", output);
	}
	cv::destroyAllWindows();
	return output;
};