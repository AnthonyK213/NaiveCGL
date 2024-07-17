#ifndef _NaiveCGL_Collection_List2_HeaderFile
#define _NaiveCGL_Collection_List2_HeaderFile

#include <vector>

#include "../Common/Type.h"

template <typename T> using Naive_List2 = ::std::vector<::std::vector<T>>;

using Naive_IntegerList2 = Naive_List2<Naive_Integer>;
using Naive_RealList2 = Naive_List2<Naive_Real>;

#endif
