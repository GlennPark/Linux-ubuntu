#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	Mat image = imread("sample.jpg", IMREAD_COLOR);
	imshow("Load Image", image);
	Mat image2 = imread("sample.png", IMREAD_COLOR);
	imshow("Load png IMage", image2);


	waitKey(0);

	return 0;
}
