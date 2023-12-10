#ifndef _NaiveCGL_Common_def_Header
#define _NaiveCGL_Common_def_Header

#ifdef _WIN32
#include <Eigen/Eigen>
#else
#include <eigen3/Eigen/Eigen>
#endif

#include <map>
#include <memory>
#include <vector>

#ifndef Naive_Export
#ifdef _WIN32
#define Naive_Export __declspec(dllexport)
#else
#define Naive_Export
#endif
#endif

template <typename T> using Naive_H = std::shared_ptr<T>;
template <typename T> using Naive_Vector3 = Eigen::Matrix<T, 3, 1>;

using Naive_Real = double;
using Naive_Integer = int;
using Naive_Vector3d = Naive_Vector3<Naive_Real>;
using Naive_Vector3i = Naive_Vector3<Naive_Integer>;

#endif
