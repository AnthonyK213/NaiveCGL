#ifndef _NaiveCGL_Math_Eigen_HeaderFile
#define _NaiveCGL_Math_Eigen_HeaderFile

#include <Eigen/Eigen>

template <typename T> using Naive_Mat3 = ::Eigen::Matrix<T, 3, 3>;
template <typename T> using Naive_Vec2 = ::Eigen::Matrix<T, 2, 1>;
template <typename T> using Naive_Vec3 = ::Eigen::Matrix<T, 3, 1>;
template <typename T> using Naive_Vec4 = ::Eigen::Matrix<T, 4, 1>;

template <Naive_Integer Dim_>
using Naive_VNd = ::Eigen::Matrix<Naive_Real, Dim_, 1>;

#endif
