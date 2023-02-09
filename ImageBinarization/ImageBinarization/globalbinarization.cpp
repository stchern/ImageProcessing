#include "globalbinarization.h"

float GlobalBinarization::OtsuMethod::Internal::varianceBetweenClass(const std::vector<float>& histogram, int threshold, int maxGrayLevel)
{
    float weight0 = 0;
    for (size_t grayLevelIdx = 0; grayLevelIdx < threshold + 1; ++grayLevelIdx)
        weight0 += histogram[grayLevelIdx];

    const float weight1 = 1.0f - weight0;

    float mu0 = 0.0f;
    float mu1 = 0.0f;

    for (size_t grayLevelIdx = 0; grayLevelIdx < threshold + 1; ++grayLevelIdx)
        mu0 += grayLevelIdx * histogram[grayLevelIdx];

    for (size_t grayLevelIdx = threshold + 1; grayLevelIdx < maxGrayLevel + 1; ++grayLevelIdx)
        mu1 += grayLevelIdx * histogram[grayLevelIdx];

    mu0 /= weight0;
    mu1 /= weight1;

    const float varianceBetweenClass = weight0 * weight1 * (mu1 - mu0) * (mu1 - mu0);

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
        if (numberOfCurrentValue > std::numeric_limits<float>::epsilon())
            numberOfNonZeroGrayValues += numberOfCurrentValue;

    int bestThreshold = 255;
    if (numberOfNonZeroGrayValues < std::numeric_limits<float>::epsilon())
        return bestThreshold;

    for (size_t grayLevelIdx = 0 ; grayLevelIdx < maxGrayLevel + 1; ++grayLevelIdx)
        histogram[(int)grayLevelIdx] /= numberOfNonZeroGrayValues;

    float maxVarianceBetweenClass = 0.0f;
    for (size_t threshold = 0; threshold < maxGrayLevel + 1; ++threshold) {
        const float currentVariance = Internal::varianceBetweenClass(histogram, threshold, maxGrayLevel);
        if (currentVariance > maxVarianceBetweenClass) {
            maxVarianceBetweenClass = currentVariance;
            bestThreshold = threshold;
        }
    }

    return bestThreshold;
}

cv::Mat GlobalBinarization::binarize(const cv::Mat& sourceImage, int threshold)
{
    cv::Mat resultImage(sourceImage.size(), CV_8UC1);
    for (size_t row = 0 ; row < sourceImage.rows; ++row)
        for (size_t col = 0 ; col < sourceImage.cols; ++col)
            resultImage.at<uchar>(row, col) = sourceImage.at<uchar>(row, col) < threshold ? 0 : 255;

    return resultImage;
}
