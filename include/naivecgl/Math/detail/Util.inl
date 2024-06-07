#include "../Util.h"

Naive_NAMESPACE_BEGIN(math);

template <typename T>
Naive_Bool Util::List2CheckBound(const Naive_List2<T> &theList2,
                                 Naive_Integer &theU, Naive_Integer &theV) {
  theU = static_cast<Naive_Integer>(theList2.size());
  if (theU == 0) {
    theV = 0;
    return Naive_True;
  }

  const Naive_List<T> &aList = theList2[0];
  theV = static_cast<Naive_Integer>(aList.size());
  for (Naive_Integer i = 1; i < theU; ++i) {
    if (theList2[i].size() != theV)
      return Naive_False;
  }

  return Naive_True;
}

Naive_NAMESPACE_END(math);
