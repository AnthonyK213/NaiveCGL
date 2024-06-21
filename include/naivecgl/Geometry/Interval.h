#ifndef _NaiveCGL_Geometry_Interval_HeaderFile
#define _NaiveCGL_Geometry_Interval_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(geometry);

class Interval final {
public:
  Naive_EXPORT Interval(Naive_Real theT0, Naive_Real theT1);

  Naive_EXPORT Interval(const Interval &theOther) = default;

  Naive_EXPORT Interval(Interval &&theOther) noexcept = default;

  Naive_EXPORT Interval &operator=(const Interval &theOther) = default;

  Naive_EXPORT Interval &operator=(Interval &&theOther) noexcept = default;

public:
  /// @brief
  /// @return
  Naive_EXPORT static const Interval &Unset() noexcept;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Bool IsDecreasing() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Bool IsIncreasing() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Bool IsSingleton() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Bool IsValid() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Real Length() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Real Max() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Real Mid() const;

  /// @brief
  /// @return
  Naive_EXPORT Naive_Real Min() const;

  /// @brief
  /// @return
  Naive_Real T0() const { return myT0; }

  /// @brief
  /// @return
  Naive_Real T1() const { return myT1; }

  void SetT0(const Naive_Real theT0) { myT0 = theT0; }

  void SetT1(const Naive_Real theT1) { myT1 = theT1; }

public:
  Naive_EXPORT static Interval FromIntersection(const Interval &theA,
                                                const Interval &theB);

  Naive_EXPORT static Interval FromUnion(const Interval &theA,
                                         const Interval &theB);

  Naive_EXPORT int32_t CompareTo(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool EpsilonEquals(const Interval &theOther,
                                        Naive_Real theEpsilon) const;

  Naive_EXPORT Naive_Bool Equals(const Interval &theOther) const;

  Naive_EXPORT void Grow(Naive_Real theValue);

  Naive_EXPORT Naive_Bool IncludesInterval(const Interval &theInterval) const;

  Naive_EXPORT Naive_Bool IncludesInterval(const Interval &theInterval,
                                           Naive_Bool theStrict) const;

  Naive_EXPORT Naive_Bool IncludesParameter(Naive_Real theT) const;

  Naive_EXPORT Naive_Bool IncludesParameter(Naive_Real theT,
                                            Naive_Bool theStrict) const;

  Naive_EXPORT void MakeIncreasing();

  Naive_EXPORT Interval
  NormalizedIntervalAt(const Interval &theIntervalParameter) const;

  Naive_EXPORT Naive_Real
  NormalizedParameterAt(Naive_Real theIntervalParameter) const;

  Naive_EXPORT Naive_Real ParameterAt(Naive_Real theNormalizedParameter) const;

  Naive_EXPORT Interval
  ParameterIntervalAt(const Interval &theNormalizedInterval) const;

  /// @brief Changes interval to [-T1, -T0].
  Naive_EXPORT void Reverse();

  /// @brief Exchanges T0 and T1.
  Naive_EXPORT void Swap();

public:
  Naive_EXPORT Naive_Bool operator!=(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool operator<(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool operator<=(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool operator==(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool operator>(const Interval &theOther) const;

  Naive_EXPORT Naive_Bool operator>=(const Interval &theOther) const;

  Naive_EXPORT const Interval operator-(Naive_Real theNumber) const;

  Naive_EXPORT const Interval operator+(Naive_Real theNumber) const;

  Naive_EXPORT Interval &operator-=(Naive_Real theNumber);

  Naive_EXPORT Interval &operator+=(Naive_Real theNumber);

private:
  Naive_Real myT0;
  Naive_Real myT1;
};

Naive_EXPORT const Interval operator-(Naive_Real theNumber,
                                      const Interval &theInterval);

Naive_EXPORT const Interval operator+(Naive_Real theNumber,
                                      const Interval &theInterval);

Naive_NAMESPACE_END(geometry);

using Naive_Interval = ::naivecgl::geometry::Interval;

#endif
