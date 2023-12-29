#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constants.h"

Naive_Namespace_Begin(math);

Naive_Export Naive_Bool EpsilonEquals(Naive_Real theX, Naive_Real theY,
                                      Naive_Real theEpsilon);

Naive_Export Naive_Bool IsValidDouble(Naive_Real theX);

Naive_Export constexpr Naive_Real ToDegrees(Naive_Real theRadians);

Naive_Export constexpr Naive_Real ToRadians(Naive_Real theDegrees);

Naive_Namespace_End(math);

#endif
