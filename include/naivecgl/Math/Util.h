#ifndef _NaiveCGL_Math_Util_HeaderFile
#define _NaiveCGL_Math_Util_HeaderFile

#include "Constants.h"

Naive_NAMESPACE_BEGIN(math);

class Util {
public:
  Naive_EXPORT static Naive_Bool
  EpsilonEquals(Naive_Real theX, Naive_Real theY,
                Naive_Real theEpsilon = math::Epsilon);

  Naive_EXPORT static Naive_Bool IsValidDouble(Naive_Real theX);

  Naive_EXPORT static Naive_Real ToDegrees(Naive_Real theRadians);

  Naive_EXPORT static Naive_Real ToRadians(Naive_Real theDegrees);
};

Naive_NAMESPACE_END(math);

#endif
