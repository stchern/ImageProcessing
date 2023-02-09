#include "opencv2/core.hpp"
#include <opencv2/opencv.hpp>

#include "ImageBinarization/globalbinarization.h"
#include "ImageBinarization/localbinarization.h"

#include <string>

int main() {    

    cv::samples::addSamplesDataSearchPath("../../images/");
    const std::string image_path = cv::samples::findFile("image.jpeg");
    const cv::Mat image = cv::imread(image_path, cv::IMREAD_ANYCOLOR);

    if (image.empty()) {
        std::cout << "Image File Not Found" << std::endl;
        std::cin.get();
        return -1;
    }

    // ------------------------------- preprocessing --------------------------------------------------------------
    cv::Mat imageGray, imageGaussianBlur, imageMedianBlur;
    if (image.channels() == 3)
        cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    else if (image.channels() == 1)
        imageGray = image;
    cv::GaussianBlur(imageGray, imageGaussianBlur, cv::Size(3, 3), 0);
    cv::medianBlur(imageGray, imageMedianBlur, 3);

    //------------------------------- global thresholding ---------------------------------------------------------

    float otsuThreshold = GlobalBinarization::OtsuMethod::bestThreshold(imageGaussianBlur);
    cv::Mat resultOtsuImage = GlobalBinarization::binarize(imageGaussianBlur, otsuThreshold);

    //------------------------------- local thresholding ----------------------------------------------------------
    const int windowSize = 5;
    const int contrastLimit = 15;
    cv::Mat resultBernsenImage = LocalBinarization::BernsenMethod::binarize(imageMedianBlur, windowSize, contrastLimit);

    // -----------------------------------------------------------------------------------------------------------
    cv::imwrite("../../images/global_otsu_image.jpg", resultOtsuImage);
    cv::imwrite("../../images/local_bernsen_image.jpg", resultBernsenImage);

    cv::waitKey(0);
    return 0;
}
