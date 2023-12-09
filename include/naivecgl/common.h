#ifndef NAIVECGL_COMMON_H
#define NAIVECGL_COMMON_H

#ifdef _WIN32
#include <Eigen/Eigen>
#else
#include <eigen3/Eigen/Eigen>

namespace Eigen {
template <typename T> using Vector3 = Matrix<T, 3, 1>;
}
#endif

#include <map>
#include <memory>
#include <vector>

#endif
