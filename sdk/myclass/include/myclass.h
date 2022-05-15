//by zr
//20220515
#ifndef MYCLASS_H
#define MYCLASS_H

#include<vector>
#include <opencv2/opencv.hpp>

using namespace std;

class ReadImage
{
public:
	ReadImage(int value1, cv::Mat value2);
	int showThershold();
	cv::Mat showImage();
	int getSum();

private:
	int threshold = 0;
	int sum = 0;
	cv::Mat image;

	void setThershold(int value1);
	void setImage(cv::Mat value2);
};

#endif