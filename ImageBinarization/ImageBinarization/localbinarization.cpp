#include "localbinarization.h"
#include <iostream>

void LocalBinarization::BernsenMethod::Internal::binarizeBlock(
        const cv::Mat& sourceImage, size_t upperRow, size_t leftCol, size_t bottomRow, size_t rightCol, int contrastLimit, int globalThreshold, cv::Mat& outImage)
{
    int minGrayLevel = 256;
    int maxGrayLevel = 0;

    for (size_t row = upperRow; row < bottomRow; ++row)
        for (size_t col = leftCol; col < rightCol ; ++col) {
            const int pixelGrayLevel = (int)sourceImage.at<uchar>(row, col);
            if (pixelGrayLevel < minGrayLevel)
                minGrayLevel = pixelGrayLevel;
            if (pixelGrayLevel > maxGrayLevel)
                maxGrayLevel = pixelGrayLevel;
        }

    int threshold = (maxGrayLevel + minGrayLevel) / 2;
    if (maxGrayLevel - minGrayLevel < contrastLimit)
        threshold = globalThreshold;

    for (size_t row = upperRow; row < bottomRow; ++row)
        for (size_t col = leftCol; col < rightCol ; ++col) {
            outImage.at<uchar>(row, col) = sourceImage.at<uchar>(row, col) < threshold ? 0 : 255;
        }

}

cv::Mat LocalBinarization::BernsenMethod::binarize(const cv::Mat& sourceImage, int windowSize, int contrastLimit, int globalThreshold)
{
    assert((windowSize > 1 && windowSize < sourceImage.rows && windowSize < sourceImage.cols) && "windowSize must be less then image height/width and greater then 1");
    assert(windowSize % 2 == 1 && "windowSize must be odd");

    cv::Mat resultImage(sourceImage.size(), CV_8UC1);

    const size_t nCols = sourceImage.cols;
    const size_t nRows = sourceImage.rows;
    const size_t halfWindowSize = windowSize / 2;

    for (size_t row = halfWindowSize; row < nRows; ++row) {
        size_t bottomRow = std::min(row + halfWindowSize + 1, nRows);
        for (size_t col = halfWindowSize; col < nCols; ++col) {
            size_t rightCol = std::min(col + halfWindowSize + 1, nCols);
            Internal::binarizeBlock(sourceImage, row - halfWindowSize, col - halfWindowSize, bottomRow, rightCol, contrastLimit, globalThreshold, resultImage);
        }
    }

    return resultImage;
}
