#include "e-board.hpp"

int main() {
	//cv::namedWindow("mainwindow", cv::WINDOW_AUTOSIZE);
	/*cv::VideoCapture capture{"tempimage.png"};
	if (!capture.isOpened())
	{
		std::cerr << "Could not open video!\n";
		return 1;
	}*/
	
	cv::Mat capture {cv::imread("tempimage.png")};
	cv::Mat frame{};

	std::vector<cv::Point2f>points {eboard::getPoints(capture)};
	if (points.size() != 4)
	{
		return 1;
	}

	cv::Mat correctPerspective{ eboard::warpPerspective(points, capture) };

	while (true)
	{
		/*capture >> frame;
		if (frame.empty())
		{
			std::cerr << "Blank frame.\n";
			return 1;
		}*/

	}
}