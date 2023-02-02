#include "e-board.hpp"

void eboard::drawCircles(int evt, int x, int y, int flags, void* param) {
	if (evt == cv::EVENT_LBUTTONDOWN) 
	{
		std::vector<cv::Point>* ptPtr = static_cast<std::vector<cv::Point>*>(param);
		ptPtr->push_back(cv::Point(x, y));
	}
}

std::vector<cv::Point> eboard::getPoints(cv::Mat image) {
	std::vector<cv::Point> points{};

	cv::namedWindow("setpoints", cv::WINDOW_AUTOSIZE);
	cv::resize(image, image, cv::Size(800, 800));

	cv::setMouseCallback("setpoints", drawCircles, (void*)&points);

	//ESC.
	while (cv::waitKey(20) != 27)
	{
		int iterator{};
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