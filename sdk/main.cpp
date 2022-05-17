#include<iostream>
#include "src/myclass.h"
#include <opencv2/opencv.hpp>


using namespace std;


int main()
{
	cv::Mat src = cv::imread("/media/qulab/2fbfe086-740c-4d24-acff-839bf21fb2c2/zr/code/calca/1.jpg", cv::IMREAD_GRAYSCALE);
	ReadImage a(0, src);
	cout << a.getSum();
	getchar();
	return 0;
}
