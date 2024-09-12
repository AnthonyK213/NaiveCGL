#ifndef _NaiveCGL_Math_Precision_HeaderFile
#define _NaiveCGL_Math_Precision_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(math);

class Precision {
public:
  static constexpr Naive_Real Zero() { return 1.e-16; }

  static constexpr Naive_Real Angular() { return 1.e-12; }

  static constexpr Naive_Real Epsilon0() { return 1e-7; }

  static constexpr Naive_Real SquareEpsilon0() {
    return Epsilon0() * Epsilon0();
  }

  static constexpr Naive_Real PEpsilon0(const Naive_Real theT = 100.0) {
    return Epsilon0() / theT;
  }

  static constexpr Naive_Real SquarePEpsilon0(const Naive_Real theT = 100.0) {
    Naive_Real PE0 = PEpsilon0(theT);
    return PE0 * PE0;
  }

  static constexpr Naive_Real Intersection() { return Epsilon0() * 0.01; }

  static constexpr Naive_Real Approximation() { return Epsilon0() * 10.0; }
};

Naive_NAMESPACE_END(math);

#endif
