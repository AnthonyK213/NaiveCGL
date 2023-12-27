#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constants.h"

Naive_Namespace_Begin(math);

Naive_Export Naive_Bool epsilonEquals(Naive_Real x, Naive_Real y,
                                      Naive_Real epsilon);

Naive_Export Naive_Bool isValidDouble(Naive_Real x);

Naive_Export constexpr Naive_Real toDegrees(Naive_Real radians);

Naive_Export constexpr Naive_Real toRadians(Naive_Real degrees);

Naive_Namespace_End(math);

#endif
