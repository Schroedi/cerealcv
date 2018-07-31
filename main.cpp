#include <iostream>
#include <cv.hpp>
#include <fstream>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>

#include "matcerealization.hpp"


namespace cereal {
void save(JSONOutputArchive& ar, const BinaryData<const unsigned char*>& m) {
    ar.saveBinaryValue(m.data, m.size);
}
void load_and_construct(JSONInputArchive& ar, construct<BinaryData<const unsigned char*>>& construct) {
    std::string tmp;
    ar.loadValue(tmp);
    auto decoded = base64::decode(tmp);
    construct(reinterpret_cast<const unsigned char*>(decoded.data()), decoded.size());
}
}

int main() {
    cv::Mat orig(2,2, CV_32FC1);

    bool useBinary = true;

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

//    // read and compare
//    {
//        cv::Mat read();
//        std::ifstream is(filename);
//        cereal::JSONInputArchive inputArchive(is);
//        inputArchive(read);
//    }


    return 0;
}
