/*
 * File: matcerealisation.hpp
 *
 * Copyright 2015 Patrik Huber
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#ifndef MATCEREALISATION_HPP_
#define MATCEREALISATION_HPP_

#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>

#include "opencv2/core/core.hpp"
#include "cereal/cereal.hpp"


namespace cereal {
void save(JSONOutputArchive& ar, const BinaryData<const unsigned char*>& m);
void load(JSONInputArchive& ar, BinaryData<unsigned char*>& m);
}

/**
 * Serialisation for OpenCV cv::Mat matrices for the serialisation
 * library cereal (http://uscilab.github.io/cereal/index.html).
 */

namespace cv {

/**
 * Serialise a cv::Mat using cereal.
 *
 * Supports all types of matrices as well as non-contiguous ones.
 *
 * @param[in] ar The archive to serialise to.
 * @param[in] mat The matrix to serialise.
 */
template<class Archive>
void save(Archive& ar, const cv::Mat& mat);

/**
 * De-serialise a cv::Mat using cereal.
 *
 * Supports all types of matrices as well as non-contiguous ones.
 *
 * @param[in] ar The archive to deserialise from.
 * @param[in] mat The matrix to deserialise into.
 */
template<class Archive>
void load(Archive& ar, cv::Mat& mat);

}

namespace cereal {
template <class Archive>
struct specialize<Archive, cv::Mat, cereal::specialization::non_member_load_save> {};

}

#endif /* MATCEREALISATION_HPP_ */
