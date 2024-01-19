#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constants.h"

Naive_NAMESPACE_BEGIN(math);

Naive_EXPORT Naive_Bool EpsilonEquals(Naive_Real theX, Naive_Real theY,
                                      Naive_Real theEpsilon);

Naive_EXPORT Naive_Bool IsValidDouble(Naive_Real theX);

Naive_EXPORT constexpr Naive_Real ToDegrees(Naive_Real theRadians);

Naive_EXPORT constexpr Naive_Real ToRadians(Naive_Real theDegrees);

Naive_NAMESPACE_END(math);

#endif
