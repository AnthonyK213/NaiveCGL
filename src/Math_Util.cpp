#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Naive_Bool EpsilonEquals(Naive_Real theX, Naive_Real theY,
                         Naive_Real theEpsilon) {
  if (std::isnan(theX) || std::isnan(theY))
    return false;

  if (theX == std::numeric_limits<double>::infinity())
    return theY == std::numeric_limits<double>::infinity();

  if (theX == -std::numeric_limits<double>::infinity())
    return theY == -std::numeric_limits<double>::infinity();

  if (std::abs(theX) < theEpsilon && std::abs(theY) < theEpsilon)
    return std::abs(theX - theY) < theEpsilon;

  if (theX >= theY - theEpsilon)
    return theX <= theY + theEpsilon;

  return false;
}

Naive_Bool IsValidDouble(Naive_Real theX) {
  if (theX != UnsetValue && !std::isinf(theX))
    return !std::isnan(theX);

  return false;
}

constexpr Naive_Real ToDegrees(Naive_Real theRadians) {
  return theRadians * 180.0 / PI;
}

constexpr Naive_Real ToRadians(Naive_Real theDegrees) {
  return theDegrees * PI / 180.0;
}

Naive_NAMESPACE_END(math);
