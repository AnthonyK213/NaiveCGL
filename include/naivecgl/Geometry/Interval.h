#ifndef _NaiveCGL_Geometry_Interval_HeaderFile
#define _NaiveCGL_Geometry_Interval_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Interval final {
public:
  Interval(Naive_Real theT0, Naive_Real theT1);

  Interval(const Interval &theOther) = default;

  Interval(Interval &&theOther) noexcept = default;

  Interval &operator=(const Interval &theOther) = default;

  Interval &operator=(Interval &&theOther) noexcept = default;

public:
  /// @brief
  /// @return
  static const Interval &Unset() noexcept;

  /// @brief
  /// @return
  Naive_Bool IsDecreasing() const;

  /// @brief
  /// @return
  Naive_Bool IsIncreasing() const;

  /// @brief
  /// @return
  Naive_Bool IsSingleton() const;

  /// @brief
  /// @return
  Naive_Bool IsValid() const;

  /// @brief
  /// @return
  Naive_Real Length() const;

  /// @brief
  /// @return
  Naive_Real Max() const;

  /// @brief
  /// @return
  Naive_Real Mid() const;

  /// @brief
  /// @return
  Naive_Real Min() const;

  /// @brief
  /// @return
  Naive_Real T0() const;

  /// @brief
  /// @return
  Naive_Real T1() const;

public:
  static Interval FromIntersection(const Interval &theA, const Interval &theB);

  static Interval FromUnion(const Interval &theA, const Interval &theB);

  int32_t CompareTo(const Interval &theOther) const;

  Naive_Bool EpsilonEquals(const Interval &theOther,
                           Naive_Real theEpsilon) const;

  Naive_Bool Equals(const Interval &theOther) const;

  void Grow(Naive_Real theValue);

  Naive_Bool IncludesInterval(const Interval &theInterval) const;

  Naive_Bool IncludesInterval(const Interval &theInterval,
                              Naive_Bool theStrict) const;

  Naive_Bool IncludesParameter(Naive_Real theT) const;

  Naive_Bool IncludesParameter(Naive_Real theT, Naive_Bool theStrict) const;

  void MakeIncreasing();

  Interval NormalizedIntervalAt(const Interval &theIntervalParameter) const;

  Naive_Real NormalizedParameterAt(Naive_Real theIntervalParameter) const;

  Naive_Real ParameterAt(Naive_Real theNormalizedParameter) const;

  Interval ParameterIntervalAt(const Interval &theNormalizedInterval) const;

  /// @brief Changes interval to [-T1, -T0].
  void Reverse();

  /// @brief Exchanges T0 and T1.
  void Swap();

public:
  Naive_Bool operator!=(const Interval &theOther) const;

  Naive_Bool operator<(const Interval &theOther) const;

  Naive_Bool operator<=(const Interval &theOther) const;

  Naive_Bool operator==(const Interval &theOther) const;

  Naive_Bool operator>(const Interval &theOther) const;

  Naive_Bool operator>=(const Interval &theOther) const;

  const Interval operator-(Naive_Real theNumber) const;

  const Interval operator+(Naive_Real theNumber) const;

  Interval &operator-=(Naive_Real theNumber);

  Interval &operator+=(Naive_Real theNumber);

private:
  Naive_Real myT0;
  Naive_Real myT1;
};

const Interval operator-(Naive_Real theNumber, const Interval &theInterval);

const Interval operator+(Naive_Real theNumber, const Interval &theInterval);

Naive_Namespace_End(geometry);

#endif
