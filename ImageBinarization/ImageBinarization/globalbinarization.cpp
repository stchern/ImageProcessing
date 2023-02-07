#include "globalbinarization.h"
#include <iostream>

float GlobalBinarization::OtsuMethod::varianceBetweenClass(const std::vector<float>& histogram, int startThreshold, int maxGrayLevel)
{
    float weight0 = 0;
    for (size_t grayLevelIdx = 0; grayLevelIdx < startThreshold; ++grayLevelIdx)
        weight0 += histogram[grayLevelIdx];

    const float weight1 = 1.0f - weight0;

    float mu0 = 0.0f;
    float mu1 = 0.0f;

    for (size_t grayLevelIdx = 0; grayLevelIdx < startThreshold; ++grayLevelIdx)
        mu0 += grayLevelIdx * histogram[grayLevelIdx];

    for (size_t grayLevelIdx = startThreshold; grayLevelIdx < maxGrayLevel + 1; ++grayLevelIdx)
        mu1 += grayLevelIdx * histogram[grayLevelIdx];

    mu0 /= weight0;
    mu1 /= weight1;

//    float variance0 = 0.0f;
//    float variance1 = 0.0f;
//    for (size_t grayLevelIdx = 0; grayLevelIdx < startThreshold; ++grayLevelIdx)
//        variance0 += (grayLevelIdx - mu0) * (grayLevelIdx - mu0) * histogram[grayLevelIdx];

//    for (size_t grayLevelIdx = startThreshold; grayLevelIdx < 256; ++grayLevelIdx)
//        variance1 += (grayLevelIdx - mu1) * (grayLevelIdx - mu1) * histogram[grayLevelIdx];

//    variance0 /= weight0;
//    variance1 /= weight1;
//    std::cout<< "weight0: " << weight0 << " weight1: " << weight1 << " mu0: " << mu0 << " mu1: " << mu1 << std::endl;
    float varianceBetweenClass = weight0 * weight1 * (mu1 - mu0) * (mu1 - mu0);
//    float varianceWithinClass = weight0 * mu0 + weight1 * mu1;

    return varianceBetweenClass;
}


int GlobalBinarization::OtsuMethod::bestThreshold(const cv::Mat& sourceImage)
{
    std::vector<float> histogram(256, 0);
    int maxGrayLevel = 0;

    for (size_t row = 0 ; row < sourceImage.rows; ++row)
        for (size_t col = 0 ; col < sourceImage.cols; ++col) {
            const uchar pixelGrayLevel = sourceImage.at<uchar>(row, col);
            ++histogram[(int)pixelGrayLevel];
            if (pixelGrayLevel > maxGrayLevel)
                maxGrayLevel = (int)pixelGrayLevel;
        }

    float numberOfNonZeroGrayValues = 0.0;
    for (float numberOfCurrentValue: histogram)
        if (numberOfCurrentValue > 1e-10)
            numberOfNonZeroGrayValues += numberOfCurrentValue;

    float value = 0.0;
    for (size_t grayLevelIdx = 0 ; grayLevelIdx < maxGrayLevel + 1; ++grayLevelIdx) {
                histogram[(int)grayLevelIdx] /= numberOfNonZeroGrayValues;
                value += histogram[(int)grayLevelIdx];
    }

    if (value - 1.0f > 1e-10)
        std::cout<< "smth goes wrong, value: " << value << std::endl;

    float maxVarianceBetweenClass = 0.0f;
    int bestThreshold = 0;
    for (int threshold = 0; threshold < maxGrayLevel; ++threshold) {
        const float currentVariance = varianceBetweenClass(histogram, threshold, maxGrayLevel);
        if (currentVariance > maxVarianceBetweenClass) {
            maxVarianceBetweenClass = currentVariance;
            bestThreshold = threshold;
        }
    }

    return bestThreshold;
}

cv::Mat GlobalBinarization::binarizeImageByThreshold(const cv::Mat& sourceImage, int threshold)
{
    cv::Mat resultImage(sourceImage.size(), CV_8UC1);
    for (size_t row = 0 ; row < sourceImage.rows; ++row)
        for (size_t col = 0 ; col < sourceImage.cols; ++col)
            resultImage.at<uchar>(row, col) = sourceImage.at<uchar>(row, col) < threshold ? 0 : 255;

    return resultImage;
}
