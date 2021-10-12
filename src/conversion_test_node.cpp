#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char * argv[]) {
    // create 16bit integer image
    const std::string fmt = sensor_msgs::image_encodings::MONO16;
    cv_bridge::CvImage im0;
    im0.image = cv::Mat(100, 100, cv_bridge::getCvType(fmt));
    im0.image = 2500;
    im0.encoding = fmt;
    std::cout << "orig type: " << im0.image.type() << std::endl;
    double max_org;
    cv::minMaxLoc(im0.image, nullptr, &max_org);
    std::cout << "orig max: " <<  max_org << std::endl;

    // convert to message and back
    sensor_msgs::CompressedImage::ConstPtr msg = im0.toCompressedImageMsg(cv_bridge::PNG);
    cv_bridge::CvImage im1 = *cv_bridge::toCvCopy(msg, fmt).get();
    std::cout << "converted type: " << im1.image.type() << std::endl;
    double max_conv;
    cv::minMaxLoc(im1.image, nullptr, &max_conv);
    std::cout << "converted max: " << max_conv << std::endl;

    return 0;
}
