#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Intv.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Intv::Intv(const Naive_Real theT0, const Naive_Real theT1)
    : myT0(theT0), myT1(theT1) {}

const Intv &Intv::Unset() noexcept {
  static Intv Interval_Unset{Constant::UnsetReal(), Constant::UnsetReal()};
  return Interval_Unset;
}

Naive_Bool Intv::IsDecreasing() const { return myT0 > myT1; }

Naive_Bool Intv::IsIncreasing() const { return myT0 < myT1; }

Naive_Bool Intv::IsSingleton() const { return IsValid() && myT0 == myT1; }

Naive_Bool Intv::IsValid() const {
  return Util::IsValidReal(myT0) && Util::IsValidReal(myT1);
}

Naive_Real Intv::Length() const { return myT1 - myT0; }

Naive_Real Intv::Max() const { return (::std::max)(myT0, myT1); }

Naive_Real Intv::Mid() const { return (myT0 + myT1) / 2.0; }

Naive_Real Intv::Min() const { return (::std::min)(myT0, myT1); }

Intv Intv::FromIntersection(const Intv &theA, const Intv &theB) {
  if (theA.IsValid() && theB.IsValid()) {
    Naive_Real aMin = (::std::max)(theA.Min(), theB.Min());
    Naive_Real aMax = (::std::min)(theA.Max(), theB.Max());

    if (aMin <= aMax) {
      return Intv(aMin, aMax);
    }
  }

  return Intv::Unset();
}

Intv Intv::FromUnion(const Intv &theA, const Intv &theB) {
  if (theA.IsValid() && theB.IsValid()) {
    Naive_Real aMin = (::std::min)(theA.Min(), theB.Min());
    Naive_Real aMax = (::std::max)(theA.Max(), theB.Max());

    return Intv(aMin, aMax);
  }

  return Intv::Unset();
}

int32_t Intv::CompareTo(const Intv &theOther) const {
  if (myT0 < theOther.myT0)
    return -1;

  if (myT0 > theOther.myT0)
    return 1;

  if (myT1 < theOther.myT1)
    return -1;

  if (myT1 > theOther.myT1)
    return 1;

  return 0;
}

Naive_Bool Intv::EpsilonEquals(const Intv &theOther,
                               Naive_Real theEpsilon) const {
  return Util::EpsilonEquals(myT0, theOther.myT0, theEpsilon) &&
         Util::EpsilonEquals(myT1, theOther.myT1, theEpsilon);
}

Naive_Bool Intv::Equals(const Intv &theOther) const {
  return *this == theOther;
}

void Intv::Grow(Naive_Real theValue) {
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

Naive_Bool Intv::IncludesInterval(const Intv &theInterval) const {
  return IncludesParameter(theInterval.myT0) &&
         IncludesParameter(theInterval.myT1);
}

Naive_Bool Intv::IncludesInterval(const Intv &theInterval,
                                  Naive_Bool theStrict) const {
  return IncludesParameter(theInterval.myT0, theStrict) &&
         IncludesParameter(theInterval.myT1, theStrict);
}

Naive_Bool Intv::IncludesParameter(Naive_Real theT) const {
  return IsValid() && Util::IsValidReal(theT) &&
         ((myT0 <= myT1 && myT0 <= theT && theT <= myT1) ||
          (myT1 <= myT0 && myT1 <= theT && theT <= myT0));
}

Naive_Bool Intv::IncludesParameter(Naive_Real theT,
                                   Naive_Bool theStrict) const {
  if (theStrict)
    return IsValid() && Util::IsValidReal(theT) &&
           ((myT0 <= myT1 && myT0 < theT && theT < myT1) ||
            (myT1 <= myT0 && myT1 < theT && theT < myT0));
  else
    return IncludesParameter(theT);
}

void Intv::MakeIncreasing() {
  if (IsDecreasing()) {
    Swap();
  }
}

Intv Intv::NormalizedIntervalAt(const Intv &theIntervalParameter) const {
  Naive_Real t = NormalizedParameterAt(theIntervalParameter.myT0);
  Naive_Real t2 = NormalizedParameterAt(theIntervalParameter.myT1);
  return Intv(t, t2);
}

Naive_Real Intv::NormalizedParameterAt(Naive_Real theIntervalParameter) const {
  if (Util::IsValidReal(theIntervalParameter)) {
    if (myT0 != myT1) {
      return (theIntervalParameter == myT1)
                 ? 1.0
                 : ((theIntervalParameter - myT0) / Length());
    }

    return myT0;
  }

  return Constant::UnsetReal();
}

Naive_Real Intv::ParameterAt(Naive_Real theNormalizedParameter) const {
  if (!Util::IsValidReal(theNormalizedParameter)) {
    return Constant::UnsetReal();
  }

  return (1.0 - theNormalizedParameter) * myT0 + theNormalizedParameter * myT1;
}

Intv Intv::ParameterIntervalAt(const Intv &theNormalizedInterval) const {
  Naive_Real t = ParameterAt(theNormalizedInterval.myT0);
  Naive_Real t2 = ParameterAt(theNormalizedInterval.myT1);

  return Intv(t, t2);
}

void Intv::Reverse() {
  Naive_Real temp = myT0;
  myT0 = -myT1;
  myT1 = -temp;
}

void Intv::Swap() { ::std::swap(myT0, myT1); }

Naive_Bool Intv::Dump(Naive_Interval_t &theIntv) const {
  if (IsValid()) {
    theIntv.t0 = myT0;
    theIntv.t1 = myT1;
    return Naive_True;
  }
  return Naive_False;
}

Naive_Bool Intv::operator!=(const Intv &theOther) const {
  return CompareTo(theOther) != 0;
}

Naive_Bool Intv::operator<(const Intv &theOther) const {
  return CompareTo(theOther) < 0;
}

Naive_Bool Intv::operator<=(const Intv &theOther) const {
  return CompareTo(theOther) <= 0;
}

Naive_Bool Intv::operator==(const Intv &theOther) const {
  return CompareTo(theOther) == 0;
}

Naive_Bool Intv::operator>(const Intv &theOther) const {
  return CompareTo(theOther) > 0;
}

Naive_Bool Intv::operator>=(const Intv &theOther) const {
  return CompareTo(theOther) >= 0;
}

const Intv Intv::operator-(Naive_Real theNumber) const {
  return Intv(myT0 - theNumber, myT1 - theNumber);
}

const Intv Intv::operator+(Naive_Real theNumber) const {
  return Intv(myT0 + theNumber, myT1 + theNumber);
}

Intv &Intv::operator-=(Naive_Real theNumber) {
  myT0 -= theNumber;
  myT1 -= theNumber;

  return *this;
}

Intv &Intv::operator+=(Naive_Real theNumber) {
  myT0 += theNumber;
  myT1 += theNumber;

  return *this;
}

const Intv operator-(Naive_Real theNumber, const Intv &interval) {
  return Intv(theNumber - interval.T0(), theNumber - interval.T1());
}

const Intv operator+(Naive_Real theNumber, const Intv &interval) {
  return Intv(theNumber + interval.T0(), theNumber + interval.T1());
}

Naive_NAMESPACE_END(math);
