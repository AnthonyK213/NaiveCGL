﻿#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Naive_Bool Util::EpsilonEquals(Naive_Real theX, Naive_Real theY,
                               Naive_Real theEpsilon) {
  if (::std::isnan(theX) || ::std::isnan(theY))
    return false;

  if (theX == ::std::numeric_limits<double>::infinity())
    return theY == ::std::numeric_limits<double>::infinity();

  if (theX == -::std::numeric_limits<double>::infinity())
    return theY == -::std::numeric_limits<double>::infinity();

  if (::std::abs(theX) < theEpsilon && ::std::abs(theY) < theEpsilon)
    return ::std::abs(theX - theY) < theEpsilon;

  if (theX >= theY - theEpsilon)
    return theX <= theY + theEpsilon;

  return false;
}

Naive_Bool Util::IsValidDouble(Naive_Real theX) {
  if (theX != Constant::UnsetValue() && !::std::isinf(theX))
    return !::std::isnan(theX);

  return false;
}

Naive_Real Util::ToDegrees(Naive_Real theRadians) {
  return theRadians * 180.0 / Constant::PI();
}

Naive_Real Util::ToRadians(Naive_Real theDegrees) {
  return theDegrees * Constant::PI() / 180.0;
}

Naive_Integer Util::Factorial(Naive_Integer theN) {
  if (theN <= 0)
    return 1;

  Naive_Integer aRes = 1;
  for (Naive_Integer i = 2; i <= theN; ++i) {
    aRes *= i;
  }

  return aRes;
}

Naive_Integer Util::Permutation(Naive_Integer theN, Naive_Integer theR) {
  if (theN < 0 || theR < 0 || theN < theR)
    return 0;

  Naive_Integer aRes = 1;
  for (Naive_Integer i = theN - theR + 1; i <= theN; ++i) {
    aRes *= i;
  }

  return aRes;
}

Naive_Integer Util::Combination(Naive_Integer theN, Naive_Integer theR) {
  return Permutation(theN, theR) / Factorial(theR);
}

Naive_NAMESPACE_END(math);
