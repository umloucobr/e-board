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
	std::vector<cv::Point2f> dstPoints {cv::Point(0,0), cv::Point(800, 0), cv::Point(0, 800), cv::Point(800, 800)};
	cv::Mat output;
	cv::Mat matrix {cv::getPerspectiveTransform(points, dstPoints)};

	cv::warpPerspective(input, output, matrix, cv::Size(800, 800));
	//cv::resize(output, output, cv::Size(800, 800));

	return output;
};

//Thanks to https://github.com/GeoffTF/CamChess for this way to get the outer corners.
std::vector<cv::Point2f> eboard::getCorners(cv::Mat& input) {
	cv::namedWindow("1", cv::WINDOW_AUTOSIZE);
	std::vector<cv::Point2f> corners{};
	std::array<float, 49> sumArray{};
	std::array<float, 49> subArray{};
	cv::Point2f interiorTopLeft{};
	cv::Point2f interiorBottomRight{};
	cv::Point2f interiorTopRight{};
	cv::Point2f interiorBottomLeft{};

	bool patternFound {cv::findChessboardCorners(input, cv::Size(7,7), corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK)};
	cv::drawChessboardCorners(input, cv::Size(7,7), corners, patternFound);
	
	{
		//Add the x and y value for each inner corner. The top left corner will have the smallest sum, and the bottom right corner will have the largest.
		int j{};
		for (auto i{ corners.begin() }; i != corners.end(); ++i, ++j) {
			sumArray[j] = i->x + i->y;
		}
		interiorTopLeft = corners[std::distance(std::begin(sumArray), std::min_element(std::begin(sumArray), std::end(sumArray)))];
		interiorBottomRight = corners[std::distance(std::begin(sumArray), std::max_element(std::begin(sumArray), std::end(sumArray)))];

	}
	{
		//Subtract the y from the x value for each inner corner. The top right corner will have the smallest diference, and the bottom left corner will have the largest.
		int j{};
		for (auto i {corners.begin()}; i != corners.end(); ++i, ++j) {
			subArray[j] = i->y - i->x;
		}
		interiorTopRight = corners[std::distance(std::begin(subArray), std::min_element(std::begin(subArray), std::end(subArray)))];
		interiorBottomLeft = corners[std::distance(std::begin(subArray), std::max_element(std::begin(subArray), std::end(subArray)))];
	}

	cv::Point2f temp {eboard::findOuterCorners(interiorTopLeft, interiorBottomRight)};
	cv::Point2f temp2 {eboard::findOuterCorners(interiorTopRight, interiorBottomLeft)};
	cv::Point2f temp3 {eboard::findOuterCorners(interiorBottomLeft, interiorTopRight)};
	cv::Point2f temp4 {eboard::findOuterCorners(interiorBottomRight, interiorTopLeft)};
	cv::circle(input, temp, 3, cv::Scalar(255, 255, 0));
	cv::circle(input, temp2, 3, cv::Scalar(255, 255, 0));
	cv::circle(input, temp3, 3, cv::Scalar(255, 255, 0));
	cv::circle(input, temp4, 3, cv::Scalar(255, 255, 0));

	while (cv::waitKey(20) != 27)
	{
		cv::imshow("1", input);
	}

	return corners;
}

/*Find the coordinates of one of the outer corners.
* point1 is the inner corner closest to the outer corner.
* point2 is the inner corner farthest from the outer corner.
*/
cv::Point2f eboard::findOuterCorners(const cv::Point2f& point1, const cv::Point2f& point2) {
	cv::Point2f point3 {point1.x + (point1.x - point2.x) / 6, point1.y + (point1.y - point2.y) / 6};
	return point3;
}

void eboard::drawCorners(cv::Mat& input, std::vector<cv::Point2f>& corners) {
	
	for (int i = 0; i < corners.size(); i++)
	{
		cv::Point point = corners[i];
		cv::circle(input, point, 3, cv::Scalar(0, 255, 0));
		cv::putText(input, std::to_string(i), point, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
	}
}

//Adapted from https://gitlab.com/Salt_Factory/opencv-chess-movement-detection-and-tracking.
void eboard::detectMovement(cv::Mat& input, std::vector<cv::Rect>& rectList) {
	
}