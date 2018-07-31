#include <iostream>
#include <cv.hpp>
#include <fstream>


#include "matcerealization.hpp"

int compareMats(const cv::Mat &img1, const cv::Mat &img2) {
    return countNonZero(img1 != img2);
}

void testCVSerial(bool useBinary) {
    std::__cxx11::string filename;
    if (useBinary)
        filename = "intr_serial.cereal";
    else
        filename = "intr_serial.json";

    cv::Mat orig(2, 2, CV_32FC1);
    cv::randu(orig, -42, 42);

    // save original intrinsics
    if (useBinary) {
        std::ofstream os(filename, std::ios_base::binary);
        cereal::PortableBinaryOutputArchive archive(os);
        archive(orig);
    } else {
        std::ofstream os(filename);
        cereal::JSONOutputArchive archive(os);
        archive(orig);
    }

    // read and compare
    cv::Mat read;
    if (useBinary) {
        std::ifstream is(filename, std::ios_base::binary);
        cereal::PortableBinaryInputArchive archive(is);
        archive(read);
    } else {
        std::ifstream is(filename);
        cereal::JSONInputArchive inputArchive(is);
        inputArchive(read);
    }

    assert(compareMats(orig, read) == 0);

    // check check
    read.at<float>(0) = 43;
    assert(compareMats(orig, read) == 1);
}


int main() {

    testCVSerial(true);
    testCVSerial(false);

    return 0;
}