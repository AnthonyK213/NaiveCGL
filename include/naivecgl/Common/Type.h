#ifndef _NaiveCGL_Common_common_HeaderFile
#define _NaiveCGL_Common_common_HeaderFile

#include <Eigen/Eigen>

#include <cstdint>

#include <list>
#include <map>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../Interface/NaiveCGL_c_types.h"

template <typename T> using Naive_List1 = ::std::vector<T>;
template <typename T> using Naive_List2 = ::std::vector<::std::vector<T>>;
template <typename T> using Naive_LinkedList = ::std::list<T>;
template <typename T> using Naive_Stack = ::std::stack<T>;
template <typename K, typename V> using Naive_Map = ::std::map<K, V>;
template <typename K, typename V> using Naive_Hash = ::std::unordered_map<K, V>;
template <typename T> using Naive_Matrix3 = ::Eigen::Matrix<T, 3, 3>;
template <typename T> using Naive_Vec2 = ::Eigen::Matrix<T, 2, 1>;
template <typename T> using Naive_Vec3 = ::Eigen::Matrix<T, 3, 1>;
template <typename T> using Naive_Vec4 = ::Eigen::Matrix<T, 4, 1>;

using Naive_Bool = bool;
using Naive_Integer = int32_t;
using Naive_Size = size_t;
using Naive_Real = double;
using Naive_ShortReal = float;
using Naive_IntegerList1 = Naive_List1<Naive_Integer>;
using Naive_IntegerList2 = Naive_List2<Naive_Integer>;
using Naive_RealList1 = Naive_List1<Naive_Real>;
using Naive_RealList2 = Naive_List2<Naive_Real>;
using Naive_Matrix3d = Naive_Matrix3<Naive_Real>;
using Naive_XY = Naive_Vec2<Naive_Real>;
using Naive_XYZ = Naive_Vec3<Naive_Real>;
using Naive_XYZW = Naive_Vec4<Naive_Real>;
using Naive_Affine3d = ::Eigen::Affine3d;

#endif
