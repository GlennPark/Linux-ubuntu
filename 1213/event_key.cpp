#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image(200, 300, CV_8U, Scalar(255));
	namedWindow("keyboard event", WINDOW_AUTOSIZE);
        imshow("keyboard event", image);	

	while (1)
	{
		int key = waitKey(100);
		if (key == 27) break;

		switch (key)
		{
			case 'a': cout << "a input" << endl; break;
			case 'b': cout << "b input" << endl; break;
			case 0x41: cout << "A input" << endl; break;
			case 66: cout << "B input" << endl; break;
				 
			case 0x51: cout << "left arrow input" << endl; break;
			case 0x52: cout << "upper arrow  input" << endl; break;
			case 0x53: cout << "right arrow input" << endl; break;
			case 0x54: cout << "down arrow input" << endl; break;
		}
	}
	return 0;
}
