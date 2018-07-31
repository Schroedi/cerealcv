//
// Created by ascadian on 7/31/18.
//

#pragma once

#include <cv.hpp>
#include "matcerealization.hpp"

class secondTest {
public:
    cv::Mat m2;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(m2);
    }
};


