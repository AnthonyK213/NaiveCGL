#ifndef _NaiveCGL_Geometry_Interval_HeaderFile
#define _NaiveCGL_Geometry_Interval_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Interval final {
public:
  Naive_Export Interval(Naive_Real theT0, Naive_Real theT1);

  Naive_Export Interval(const Interval &theOther) = default;

  Naive_Export Interval(Interval &&theOther) noexcept = default;

  Naive_Export Interval &operator=(const Interval &theOther) = default;

  Naive_Export Interval &operator=(Interval &&theOther) noexcept = default;

public:
  /// @brief
  /// @return
  Naive_Export static const Interval &Unset() noexcept;

  /// @brief
  /// @return
  Naive_Export Naive_Bool IsDecreasing() const;

  /// @brief
  /// @return
  Naive_Export Naive_Bool IsIncreasing() const;

  /// @brief
  /// @return
  Naive_Export Naive_Bool IsSingleton() const;

  /// @brief
  /// @return
  Naive_Export Naive_Bool IsValid() const;

  /// @brief
  /// @return
  Naive_Export Naive_Real Length() const;

  /// @brief
  /// @return
  Naive_Export Naive_Real Max() const;

  /// @brief
  /// @return
  Naive_Export Naive_Real Mid() const;

  /// @brief
  /// @return
  Naive_Export Naive_Real Min() const;

  /// @brief
  /// @return
  Naive_Real T0() const { return myT0; }

  /// @brief
  /// @return
  Naive_Real T1() const { return myT1; }

public:
  Naive_Export static Interval FromIntersection(const Interval &theA,
                                                const Interval &theB);

  Naive_Export static Interval FromUnion(const Interval &theA,
                                         const Interval &theB);

  Naive_Export int32_t CompareTo(const Interval &theOther) const;

  Naive_Export Naive_Bool EpsilonEquals(const Interval &theOther,
                                        Naive_Real theEpsilon) const;

  Naive_Export Naive_Bool Equals(const Interval &theOther) const;

  Naive_Export void Grow(Naive_Real theValue);

  Naive_Export Naive_Bool IncludesInterval(const Interval &theInterval) const;

  Naive_Export Naive_Bool IncludesInterval(const Interval &theInterval,
                                           Naive_Bool theStrict) const;

  Naive_Export Naive_Bool IncludesParameter(Naive_Real theT) const;

  Naive_Export Naive_Bool IncludesParameter(Naive_Real theT,
                                            Naive_Bool theStrict) const;

  Naive_Export void MakeIncreasing();

  Naive_Export Interval
  NormalizedIntervalAt(const Interval &theIntervalParameter) const;

  Naive_Export Naive_Real
  NormalizedParameterAt(Naive_Real theIntervalParameter) const;

  Naive_Export Naive_Real ParameterAt(Naive_Real theNormalizedParameter) const;

  Naive_Export Interval
  ParameterIntervalAt(const Interval &theNormalizedInterval) const;

  /// @brief Changes interval to [-T1, -T0].
  Naive_Export void Reverse();

  /// @brief Exchanges T0 and T1.
  Naive_Export void Swap();

public:
  Naive_Export Naive_Bool operator!=(const Interval &theOther) const;

  Naive_Export Naive_Bool operator<(const Interval &theOther) const;

  Naive_Export Naive_Bool operator<=(const Interval &theOther) const;

  Naive_Export Naive_Bool operator==(const Interval &theOther) const;

  Naive_Export Naive_Bool operator>(const Interval &theOther) const;

  Naive_Export Naive_Bool operator>=(const Interval &theOther) const;

  Naive_Export const Interval operator-(Naive_Real theNumber) const;

  Naive_Export const Interval operator+(Naive_Real theNumber) const;

  Naive_Export Interval &operator-=(Naive_Real theNumber);

  Naive_Export Interval &operator+=(Naive_Real theNumber);

private:
  Naive_Real myT0;
  Naive_Real myT1;
};

Naive_Export const Interval operator-(Naive_Real theNumber,
                                      const Interval &theInterval);

Naive_Export const Interval operator+(Naive_Real theNumber,
                                      const Interval &theInterval);

Naive_Namespace_End(geometry);

#endif
