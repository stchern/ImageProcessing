#ifndef LOCALBINARIZATION_H
#define LOCALBINARIZATION_H
#include "opencv2/core.hpp"

namespace LocalBinarization
{

namespace BernsenMethod {

namespace Internal {

void binarizeBlock(const cv::Mat& sourceImage, size_t upperRow, size_t leftCol, size_t bottomRow, size_t rightCol, int contrastLimit, int globalThreshold, cv::Mat& outImage);

}
cv::Mat binarize(const cv::Mat& sourceImage, int windowSize, int contrastLimit, int globalThreshold = 255);

}


};

#endif // LOCALBINARIZATION_H
