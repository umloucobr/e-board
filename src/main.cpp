#include "e-board.hpp"

int main() {
	cv::namedWindow("mainwindow", cv::WINDOW_AUTOSIZE);
	cv::Mat frame {cv::imread("1.jpeg")};
	//cv::VideoCapture capture{"1.mp4"};
	/*if (!capture.isOpened())
	{
		std::cerr << "Could not open video!\n";
		return 1;
	}*/
	
	//cv::Mat frame{};
	bool getPoints {true};
	bool getCorners {true};
	std::vector<cv::Point2f> points{};
	std::vector<cv::Point2f> corners{};

	//cv::Mat background {};
	//cv::Mat foregroundMask{};

	//bool movement {false};
	//auto backSub {cv::createBackgroundSubtractorMOG2()};
	//backSub->setBackgroundRatio(0.5);

	while (true)
	{
		//capture >> frame;
		//if (frame.empty())
		//{
			//std::cout << "Blank frame.\n";
			//return 0;
		//}

		if (getPoints)
		{
			points = eboard::getPoints(frame); //Get points for the warp.
			if (points.size() != 4)
			{
				return 1;
			}

			getPoints = false;
		}

		cv::Mat correctPerspective {eboard::warpPerspective(points, frame)}; //Warp.

		if (getCorners)
		{
			corners = eboard::getCorners(correctPerspective); //Get the corners inside the board.
			getCorners = false;
		}

		//backSub->apply(correctPerspective, foregroundMask);
		//backSub->getBackgroundImage(background);

		//std::vector<cv::Rect> rectList{};

		eboard::drawCorners(correctPerspective, corners);

		if (cv::waitKey(20) != 27)
		{
			cv::imshow("mainwindow", correctPerspective);
		}
	}
	cv::destroyAllWindows();
	return 0;
}