#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat m1(4, 3, CV_32FC3);

	cout << "demention = " << m1.dims << endl;
	cout << "i" << m1.rows << endl;
	cout << "i" << m1.cols << endl;
	cout << "i" << m1.size() << endl;

	cout << "i" << m1.total() << endl;
	cout << "i" << m1.elemSize() << endl;
	cout << "i" << m1.elemSize1() << endl << endl;

	cout << "i" << m1.type() << endl;
	cout << "i" << ((m1.channels() -1) << 3) + m1.depth() << endl;
	cout << "i" << m1.depth() << endl;
	cout << "" << m1.channels<< endl<<endl;
	cout << "step = " << m1.step << endl;
	cout << "step1() = " << m1.step1()<< endl;

	return 0;
}		

