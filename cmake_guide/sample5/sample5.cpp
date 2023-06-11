#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, char* argv[]) {
    std::cout << "CMake Sample 5:" << std::endl;
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " PathToImage " << std::endl;
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cout << "Load image failed" << std::endl;
        return -1;
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", image);

    cv::waitKey(0);
    return 0;
}
