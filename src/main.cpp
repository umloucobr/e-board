#include "e-board.hpp"

int main() {
	cv::namedWindow("mainwindow", cv::WINDOW_AUTOSIZE);
	/*cv::VideoCapture capture{"tempimage.png"};
	if (!capture.isOpened())
	{
		std::cerr << "Could not open video!\n";
		return 1;
	}*/
	
	cv::Mat capture {cv::imread("1.jpeg")};
	cv::Mat frame{};

	std::vector<cv::Point2f>points {eboard::getPoints(capture)}; //Get points for the warp.
	if (points.size() != 4)
	{
		return 1;
	}

	cv::Mat correctPerspective {eboard::warpPerspective(points, capture)}; //Warp.
	std::vector<cv::Point2f> corners {eboard::getSquares(correctPerspective)}; //Get the corners inside the board.

	bool movement {false};
	auto backSub {cv::createBackgroundSubtractorMOG2()};
	backSub->setBackgroundRatio(0.5);
	
	while (cv::waitKey(20) != 27)
	{
		cv::imshow("mainwindow", correctPerspective);
	}
	cv::destroyAllWindows();

	while (true)
	{
		/*capture >> frame;
		if (frame.empty())
		{
			std::cerr << "Blank frame.\n";
			return 1;
		}*/

	}
	return 0;
}