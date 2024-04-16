#ifndef _NaiveCGL_Math_Constant_HeaderFile
#define _NaiveCGL_Math_Constant_HeaderFile

#include <naivecgl/Common/Type.h>

#include <cmath>

Naive_NAMESPACE_BEGIN(math);

class Constant {
public:
  static constexpr Naive_Real PI() { return 3.14159265358979323846; }

  static constexpr Naive_Real DefaultAngleTolerance() { return PI() / 180.0; }

  static constexpr Naive_Real DefaultDistanceToleranceMillimeters() {
    return 1e-2;
  }

  static constexpr Naive_Real Epsilon() { return 2.2204460492503131e-16; }

  static constexpr Naive_Real HalfPI() { return PI() / 2.0; }

  static constexpr Naive_Real QuaterPI() { return PI() / 4.0; }

  static constexpr Naive_Real SqrtEpsilon() { return 1.490116119385000000e-8; }

  static constexpr Naive_Real Tau() { return PI() * 2.0; }

  static constexpr Naive_Real TwoPI() { return Tau(); }

  static constexpr Naive_Real ZeroTolerance() {
    return 2.3283064365386962890625e-10;
  }

  static constexpr Naive_Real UnsetReal() { return -1.23432101234321e+308; }

  static constexpr Naive_ShortReal UnsetShortReal() { return -1.234321e+38f; }

  static constexpr Naive_Integer UnsetIntIndex() { return INT_MIN + 1; }
};

Naive_NAMESPACE_END(math);

#endif
