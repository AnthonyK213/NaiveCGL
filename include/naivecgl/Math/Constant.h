#ifndef _NaiveCGL_Math_Constant_HeaderFile
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

  static constexpr Naive_Real MinReal() { return DBL_MIN; }

  static constexpr Naive_Real MaxReal() { return DBL_MAX; }

  static constexpr Naive_Real Infinite() { return 2.e+100; }

  /// Unset values.

  static constexpr Naive_Real UnsetPositiveReal() { return 2.1e+100; }

  static constexpr Naive_Real UnsetReal() { return -UnsetPositiveReal(); }
};

Naive_NAMESPACE_END(math);

#endif
