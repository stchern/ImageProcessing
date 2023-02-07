#include "opencv2/core.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

int main() {    

    cv::samples::addSamplesDataSearchPath("../../images/");
    const std::string image_path = cv::samples::findFile("images.png");
    std::cout<< "image path: " << image_path << std::endl;
    const cv::Mat image = cv::imread(image_path, cv::IMREAD_ANYCOLOR);

    if (image.empty()) {
        std::cout << "Image File Not Found" << std::endl;
        std::cin.get();
        return -1;
    }

    cv::Mat imageGray, imageBlur;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imageGray, imageBlur, cv::Size(7, 7), 5);



    cv::imshow("Original image", image);
    cv::imshow("Gray image", imageGray);
    cv::imshow("Blured image", imageBlur);

    cv::imwrite("../../images/new_image.png", image);

    cv::waitKey(0);
    return 0;
}
