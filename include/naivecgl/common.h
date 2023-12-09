#ifndef NAIVECGL_COMMON_H
#define NAIVECGL_COMMON_H

#include <eigen3/Eigen/Eigen>

#ifdef __linux__
namespace Eigen {
template <typename T> using Vector3 = Matrix<T, 3, 1>;
}
#endif

#include <map>
#include <memory>
#include <vector>

#endif
