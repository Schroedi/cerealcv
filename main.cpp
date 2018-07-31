#include <iostream>
#include <cv.hpp>
#include <fstream>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>

#include "matcerealization.hpp"


int main() {
    cv::Mat orig(2,2, CV_32FC1);

    bool useBinary = false;

    std::string filename;
    if (useBinary)
        filename = "intr_serial.cereal";
    else
        filename = "intr_serial.json";

    // save original intrinsics
    if (useBinary) {
        std::ofstream os(filename, std::ios::binary);
        cereal::PortableBinaryOutputArchive archive(os);
        archive(orig);
    } else {
       std::ofstream os(filename);
       cereal::JSONOutputArchive archive(os);
       archive(orig);
    }

    // read and compare
    {
        cv::Mat read();

        if (useBinary) {
            std::ifstream is(filename, std::ios::binary);
            cereal::PortableBinaryInputArchive inputArchive(is);
            inputArchive(read);
        } else {
            std::ifstream is(filename);
            cereal::JSONInputArchive inputArchive(is);
            inputArchive(read);
        }
    }


    return 0;
}
