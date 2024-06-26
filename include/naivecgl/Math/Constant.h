﻿#ifndef _NaiveCGL_Math_Constant_HeaderFile
#define _NaiveCGL_Math_Constant_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

#include <cmath>

Naive_NAMESPACE_BEGIN(math);

class Constant {
public:
  /// Math constants.

  static constexpr Naive_Real PI() { return 3.14159265358979323846; }

  static constexpr Naive_Real HalfPI() { return PI() / 2.0; }

  static constexpr Naive_Real QuaterPI() { return PI() / 4.0; }

  static constexpr Naive_Real Tau() { return PI() * 2.0; }

  static constexpr Naive_Real TwoPI() { return Tau(); }

  /// Limits.

  static constexpr Naive_Real MaxReal() { return 1.7976931348623158e+308; }

  static constexpr Naive_Real MinReal() { return 2.22507385850720200e-308; }

  /// Unset values.

  static constexpr Naive_Real UnsetPositiveReal() {
    return 1.23432101234321e+308;
  }

  static constexpr Naive_Real UnsetReal() { return -UnsetPositiveReal(); }

  static constexpr Naive_ShortReal UnsetShortReal() { return -1.234321e+38f; }

  static constexpr Naive_Integer UnsetIntIndex() { return -2147483647; }

  /// Tolerance.

  static constexpr Naive_Real Epsilon() { return 2.2204460492503131e-16; }

  static constexpr Naive_Real SqrtEpsilon() { return 1.490116119385000000e-8; }

  static constexpr Naive_Real ZeroTolerance() {
    return 2.3283064365386962890625e-10;
  }

  static constexpr Naive_Real DefaultATol() {
    return PI() / 360.0; /* 0.5 deg */
  }

  static constexpr Naive_Real DefaultDTol() { return 1e-3; }

  static constexpr Naive_Real DefaultVTol() { return 3. * DefaultDTol(); }

  static constexpr Naive_Real DefaultETol() { return 2. * DefaultDTol(); }

  static constexpr Naive_Real DefaultFTol() { return DefaultDTol(); }
};

Naive_NAMESPACE_END(math);

#endif
