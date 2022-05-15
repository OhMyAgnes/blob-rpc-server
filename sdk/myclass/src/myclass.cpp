//by zr
//20220515
#include "myclass.h"

ReadImage::ReadImage(int value1, cv::Mat value2)
{
	setThershold(value1);
	setImage(value2);
}

void ReadImage::setThershold(int value1)
{
	threshold = value1;
}

void ReadImage::setImage(cv::Mat value2)
{
	image = value2;
}

int ReadImage::showThershold()
{
	return threshold;
}

cv::Mat ReadImage::showImage()
{
	return image;
}


int ReadImage::getSum()
{
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			if (image.at<uchar>(row, col) > threshold)
				sum++;
		}
	}
	return sum;
}