#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image1 = imread("./lena.bmp",0);
	Mat image2 = imread("./mandrill.bmp",0);

	CV_Assert(image1.data && image2.data);

	Mat dif_img, abs_dif1, abs_dif2;
	image1.convertTo(image1, CV_16S);
	image2.convertTo(image2, CV_16S);
	subtract(image1, image2, dif_img);
	
	Rect roi(10, 10, 7, 3);
	cout << endl << dif_img(roi) << endl;
	abs_dif1 = abs(dif_img);

	image1.convertTo(image1, CV_8U);
	image2.convertTo(image2, CV_8U);


	absdiff(image1, image2, abs_dif2);
	cout << endl << dif_img(roi) << endl << endl;
}

