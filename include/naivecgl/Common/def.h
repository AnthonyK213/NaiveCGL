﻿#ifndef _NaiveCGL_Common_def_HeaderFile
#define _NaiveCGL_Common_def_HeaderFile

#include <Eigen/Eigen>

#include <cstdint>

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <naivecgl/Interface/NaiveCGL_c_types.h>

#ifndef Naive_EXPORT
#ifdef _WIN32
#define Naive_EXPORT __declspec(dllexport)
#else
#define Naive_EXPORT
#endif
#endif

#define Naive_NAMESPACE_BEGIN(ns)                                              \
  namespace naivecgl {                                                         \
  namespace ns {
#define Naive_NAMESPACE_END(ns)                                                \
  }                                                                            \
  }

template <typename T> using Naive_H = std::shared_ptr<T>;
template <typename T> using Naive_List = std::vector<T>;
template <typename K, typename V> using Naive_Map = std::map<K, V>;
template <typename K, typename V> using Naive_Hash = std::unordered_map<K, V>;

template <typename T> using Naive_Matrix3 = Eigen::Matrix<T, 3, 3>;
template <typename T> using Naive_Vector2 = Eigen::Matrix<T, 2, 1>;
template <typename T> using Naive_Vector3 = Eigen::Matrix<T, 3, 1>;

using Naive_Bool = bool;
using Naive_Real = double;
using Naive_Integer = int32_t;

using Naive_Matrix3d = Naive_Matrix3<Naive_Real>;

#endif
