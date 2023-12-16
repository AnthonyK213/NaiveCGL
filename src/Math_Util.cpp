#include <naivecgl/Math/Util.h>

Naive_Namespace_Begin(math);

Naive_Bool epsilonEquals(Naive_Real x, Naive_Real y, Naive_Real epsilon) {
  if (std::isnan(x) || std::isnan(y))
    return false;

  if (x == std::numeric_limits<double>::infinity())
    return y == std::numeric_limits<double>::infinity();

  if (x == -std::numeric_limits<double>::infinity())
    return y == -std::numeric_limits<double>::infinity();

  if (std::abs(x) < epsilon && std::abs(y) < epsilon)
    return std::abs(x - y) < epsilon;

  if (x >= y - epsilon)
    return x <= y + epsilon;

  return false;
}

Naive_Bool isValidDouble(Naive_Real x) {
  if (x != UnsetValue && !std::isinf(x))
    return !std::isnan(x);

  return false;
}

constexpr Naive_Real toDegrees(Naive_Real radians) {
  return radians * 180.0 / PI;
}

constexpr Naive_Real toRadians(Naive_Real degrees) {
  return degrees * PI / 180.0;
}

Naive_Namespace_End(math);
