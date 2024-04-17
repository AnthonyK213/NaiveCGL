﻿#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constant.h"

Naive_NAMESPACE_BEGIN(math);

class Util {
public:
  Naive_EXPORT static Naive_Bool
  EpsilonEquals(Naive_Real theX, Naive_Real theY,
                Naive_Real theEpsilon = math::Constant::Epsilon());

  Naive_EXPORT static Naive_Bool IsValidReal(Naive_Real theX);

  Naive_EXPORT static Naive_Real ToDegrees(Naive_Real theRadians);

  Naive_EXPORT static Naive_Real ToRadians(Naive_Real theDegrees);

  Naive_EXPORT static Naive_Integer Factorial(Naive_Integer theN);

  Naive_EXPORT static Naive_Integer Permutation(Naive_Integer theN,
                                                Naive_Integer theR);

  Naive_EXPORT static Naive_Integer Combination(Naive_Integer theN,
                                                Naive_Integer theR);

  template <typename T>
  static Naive_Bool List2CheckBound(const Naive_List2<T> &theList2,
                                    Naive_Integer &theU, Naive_Integer &theV);
};

Naive_NAMESPACE_END(math);

#include "detail/Util.inl"

#endif
