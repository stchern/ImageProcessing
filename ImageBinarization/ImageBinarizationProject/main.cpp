#include "opencv2/core.hpp"
#include <opencv2/opencv.hpp>
#include "ImageBinarization/globalbinarization.h"

#include <iostream>
#include <string>

int main() {    

    cv::samples::addSamplesDataSearchPath("../../images/");
    const std::string image_path = cv::samples::findFile("doc.png");
    const cv::Mat image = cv::imread(image_path, cv::IMREAD_ANYCOLOR);

    if (image.empty()) {
        std::cout << "Image File Not Found" << std::endl;
        std::cin.get();
        return -1;
    }

    cv::Mat imageGray, imageBlur;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imageGray, imageBlur, cv::Size(7, 7), 2);

    float otsuThreshold = GlobalBinarization::OtsuMethod::bestThreshold(imageGray);
    cv::Mat resultOtsuImage = GlobalBinarization::binarizeImageByThreshold(imageGray, otsuThreshold);
    std::cout<< "threshold: " << otsuThreshold << std::endl;

    cv::Mat resultCVOtsuImage;
    double cv_threshold = cv::threshold(imageGray, resultCVOtsuImage, 0, 255, cv::THRESH_OTSU);
    std::cout<< "cv_threshold: " << cv_threshold << std::endl;

    cv::imshow("Original image", image);
    cv::imshow("Blured image", imageBlur);
    cv::imshow("Otsu binarized image", resultOtsuImage);
    cv::imshow("Otsu CV binarized image", resultCVOtsuImage);

    cv::imwrite("../../images/otsu_image.png", resultOtsuImage);
    cv::imwrite("../../images/otsu_cv_image.png", resultCVOtsuImage);

    cv::waitKey(0);
    return 0;
}
