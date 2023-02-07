#ifndef GLOBALBINARIZATION_H
#define GLOBALBINARIZATION_H
#include "opencv2/core.hpp"


namespace GlobalBinarization
{

namespace OtsuMethod {

float varianceBetweenClass(const std::vector<float>& histogram, int startThreshold, int maxGrayLevel);
int bestThreshold(const cv::Mat& sourceImage);

}

cv::Mat binarizeImageByThreshold(const cv::Mat& sourceImage, int threshold);

};

#endif // GLOBALBINARIZATION_H
