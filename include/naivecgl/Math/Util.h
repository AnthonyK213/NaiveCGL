#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constants.h"

Naive_NAMESPACE_BEGIN(math);

Naive_EXPORT Naive_Bool EpsilonEquals(Naive_Real theX, Naive_Real theY,
                                      Naive_Real theEpsilon = math::Epsilon);

Naive_EXPORT Naive_Bool IsValidDouble(Naive_Real theX);

Naive_EXPORT Naive_Real ToDegrees(Naive_Real theRadians);

Naive_EXPORT Naive_Real ToRadians(Naive_Real theDegrees);

Naive_NAMESPACE_END(math);

#endif
