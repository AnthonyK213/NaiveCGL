#include <naivecgl/Geometry/Interval.h>
#include <naivecgl/Math/Util.h>

Naive_Namespace_Begin(geometry);

Interval::Interval(Naive_Real theT0, Naive_Real theT1)
    : myT0(theT0), myT1(theT1) {}

const Interval &Interval::Unset() noexcept {
  static Interval Interval_Unset{naivecgl::math::UnsetValue,
                                 naivecgl::math::UnsetValue};
  return Interval_Unset;
}

Naive_Bool Interval::IsDecreasing() const { return myT0 > myT1; }

Naive_Bool Interval::IsIncreasing() const { return myT0 < myT1; }

Naive_Bool Interval::IsSingleton() const { return IsValid() && myT0 == myT1; }

Naive_Bool Interval::IsValid() const {
  return naivecgl::math::IsValidDouble(myT0) &&
         naivecgl::math::IsValidDouble(myT1);
}

Naive_Real Interval::Length() const { return myT1 - myT0; }

Naive_Real Interval::Max() const { return (std::max)(myT0, myT1); }

Naive_Real Interval::Mid() const { return (myT0 + myT1) / 2.0; }

Naive_Real Interval::Min() const { return (std::min)(myT0, myT1); }

Interval Interval::FromIntersection(const Interval &theA,
                                    const Interval &theB) {
  if (theA.IsValid() && theB.IsValid()) {
    Naive_Real aMin = (std::max)(theA.Min(), theB.Min());
    Naive_Real aMax = (std::min)(theA.Max(), theB.Max());

    if (aMin <= aMax) {
      return Interval(aMin, aMax);
    }
  }

  return Interval::Unset();
}

Interval Interval::FromUnion(const Interval &theA, const Interval &theB) {
  if (theA.IsValid() && theB.IsValid()) {
    Naive_Real aMin = (std::min)(theA.Min(), theB.Min());
    Naive_Real aMax = (std::max)(theA.Max(), theB.Max());

    return Interval(aMin, aMax);
  }

  return Interval::Unset();
}

int32_t Interval::CompareTo(const Interval &theOther) const {
  if (myT0 < theOther.myT0) {
    return -1;
  }

  if (myT0 > theOther.myT0) {
    return 1;
  }

  if (myT1 < theOther.myT1) {
    return -1;
  }

  if (myT1 > theOther.myT1) {
    return 1;
  }

  return 0;
}

Naive_Bool Interval::EpsilonEquals(const Interval &theOther,
                                   Naive_Real theEpsilon) const {
  return naivecgl::math::EpsilonEquals(myT0, theOther.myT0, theEpsilon) &&
         naivecgl::math::EpsilonEquals(myT1, theOther.myT1, theEpsilon);
}

Naive_Bool Interval::Equals(const Interval &theOther) const {
  return *this == theOther;
}

void Interval::Grow(Naive_Real theValue) {
  if (IsDecreasing()) {
    Swap();
  }

  if (myT0 > theValue) {
    myT0 = theValue;
  }

  if (myT1 < theValue) {
    myT1 = theValue;
  }
}

Naive_Bool Interval::IncludesInterval(const Interval &theInterval) const {
  return IncludesInterval(theInterval, false);
}

Naive_Bool Interval::IncludesInterval(const Interval &theInterval,
                                      Naive_Bool theStrict) const {
  return IncludesParameter(theInterval.myT0, theStrict) &&
         IncludesParameter(theInterval.myT1, theStrict);
}

Naive_Bool Interval::IncludesParameter(Naive_Real theT) const {
  return IncludesParameter(theT, false);
}

Naive_Bool Interval::IncludesParameter(Naive_Real theT,
                                       Naive_Bool theStrict) const {
  if (!naivecgl::math::IsValidDouble(theT)) {
    return false;
  }
  if (theStrict) {
    return (myT0 <= myT1 && myT0 < theT && theT < myT1) ||
           (myT1 <= myT0 && myT1 < theT && theT < myT0);
  } else {
    return (myT0 <= myT1 && myT0 <= theT && theT <= myT1) ||
           (myT1 <= myT0 && myT1 <= theT && theT <= myT0);
  }
}

void Interval::MakeIncreasing() {
  if (IsDecreasing()) {
    Swap();
  }
}

Interval
Interval::NormalizedIntervalAt(const Interval &theIntervalParameter) const {
  Naive_Real t = NormalizedParameterAt(theIntervalParameter.myT0);
  Naive_Real t2 = NormalizedParameterAt(theIntervalParameter.myT1);
  return Interval(t, t2);
}

Naive_Real
Interval::NormalizedParameterAt(Naive_Real theIntervalParameter) const {
  if (naivecgl::math::IsValidDouble(theIntervalParameter)) {
    if (myT0 != myT1) {
      return (theIntervalParameter == myT1)
                 ? 1.0
                 : ((theIntervalParameter - myT0) / Length());
    }

    return myT0;
  }

  return naivecgl::math::UnsetValue;
}

Naive_Real Interval::ParameterAt(Naive_Real theNormalizedParameter) const {
  if (!naivecgl::math::IsValidDouble(theNormalizedParameter)) {
    return naivecgl::math::UnsetValue;
  }

  return (1.0 - theNormalizedParameter) * myT0 + theNormalizedParameter * myT1;
}

Interval
Interval::ParameterIntervalAt(const Interval &theNormalizedInterval) const {
  Naive_Real t = ParameterAt(theNormalizedInterval.myT0);
  Naive_Real t2 = ParameterAt(theNormalizedInterval.myT1);

  return Interval(t, t2);
}

void Interval::Reverse() {
  Naive_Real temp = myT0;
  myT0 = -myT1;
  myT1 = -temp;
}

void Interval::Swap() { std::swap(myT0, myT1); }

Naive_Bool Interval::operator!=(const Interval &theOther) const {
  return CompareTo(theOther) != 0;
}

Naive_Bool Interval::operator<(const Interval &theOther) const {
  return CompareTo(theOther) < 0;
}

Naive_Bool Interval::operator<=(const Interval &theOther) const {
  return CompareTo(theOther) <= 0;
}

Naive_Bool Interval::operator==(const Interval &theOther) const {
  return CompareTo(theOther) == 0;
}

Naive_Bool Interval::operator>(const Interval &theOther) const {
  return CompareTo(theOther) > 0;
}

Naive_Bool Interval::operator>=(const Interval &theOther) const {
  return CompareTo(theOther) >= 0;
}

const Interval Interval::operator-(Naive_Real theNumber) const {
  return Interval(myT0 - theNumber, myT1 - theNumber);
}

const Interval Interval::operator+(Naive_Real theNumber) const {
  return Interval(myT0 + theNumber, myT1 + theNumber);
}

Interval &Interval::operator-=(Naive_Real theNumber) {
  myT0 -= theNumber;
  myT1 -= theNumber;

  return *this;
}

Interval &Interval::operator+=(Naive_Real theNumber) {
  myT0 += theNumber;
  myT1 += theNumber;

  return *this;
}

const Interval operator-(Naive_Real theNumber, const Interval &interval) {
  return Interval(theNumber - interval.T0(), theNumber - interval.T1());
}

const Interval operator+(Naive_Real theNumber, const Interval &interval) {
  return Interval(theNumber + interval.T0(), theNumber + interval.T1());
}

Naive_Namespace_End(geometry);
