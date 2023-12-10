#ifndef _NaiveCGL__common_Header
#define _NaiveCGL__common_Header

#ifdef _WIN32
#include <Eigen/Eigen>
#else
#include <eigen3/Eigen/Eigen>
#endif

#include <map>
#include <memory>
#include <vector>

template <typename T> using Naive_Vector3 = Eigen::Matrix<T, 3, 1>;

using Naive_Real = double;
using Naive_Integer = int;
using Naive_Vector3d = Naive_Vector3<Naive_Real>;
using Naive_Vector3i = Naive_Vector3<Naive_Integer>;

#endif
