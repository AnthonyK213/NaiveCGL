#ifndef _NaiveCGL_Collection_List1_HeaderFile
#define _NaiveCGL_Collection_List1_HeaderFile

#include <vector>

#include "../Common/Type.h"

template <typename T> using Naive_List1 = ::std::vector<T>;

using Naive_IntegerList1 = Naive_List1<Naive_Integer>;
using Naive_RealList1 = Naive_List1<Naive_Real>;

#endif
