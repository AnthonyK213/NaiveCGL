#ifndef _NaiveCGL_Geometry_Interval_Header
#define _NaiveCGL_Geometry_Interval_Header

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Interval final {
public:
  /// @brief
  /// @param t0
  /// @param t1
  Interval(Naive_Real t0, Naive_Real t1);

  /// @brief
  /// @param interval
  Interval(const Interval &interval) = default;

  /// @brief
  /// @param interval
  Interval(Interval &&interval) noexcept = default;

  /// @brief
  /// @param interval
  /// @return
  Interval &operator=(const Interval &interval) = default;

  /// @brief
  /// @param interval
  /// @return
  Interval &operator=(Interval &&interval) noexcept = default;

public:
  /// @brief
  /// @return
  static const Interval &unset() noexcept;

  /// @brief
  /// @return
  Naive_Bool isDecreasing() const;

  /// @brief
  /// @return
  Naive_Bool isIncreasing() const;

  /// @brief
  /// @return
  Naive_Bool isSingleton() const;

  /// @brief
  /// @return
  Naive_Bool isValid() const;

  /// @brief
  /// @return
  Naive_Real length() const;

  /// @brief
  /// @return
  Naive_Real max_() const;

  /// @brief
  /// @return
  Naive_Real mid() const;

  /// @brief
  /// @return
  Naive_Real min_() const;

  /// @brief
  /// @return
  Naive_Real t0() const;

  /// @brief
  /// @return
  Naive_Real t1() const;

public:
  /// @brief
  /// @param a
  /// @param b
  /// @return
  static Interval fromIntersection(const Interval &a, const Interval &b);

  /// @brief
  /// @param a
  /// @param b
  /// @return
  static Interval fromUnion(const Interval &a, const Interval &b);

  /// @brief
  /// @param other
  /// @return
  int32_t compareTo(const Interval &other) const;

  /// @brief
  /// @param other
  /// @param epsilon
  /// @return
  Naive_Bool epsilonEquals(const Interval &other, Naive_Real epsilon) const;

  /// @brief
  /// @param other
  /// @return
  Naive_Bool equals(const Interval &other) const;

  /// @brief
  /// @param value
  void grow(Naive_Real value);

  /// @brief
  /// @param interval
  /// @return
  Naive_Bool includesInterval(const Interval &interval) const;

  /// @brief
  /// @param interval
  /// @param strict
  /// @return
  Naive_Bool includesInterval(const Interval &interval,
                              Naive_Bool strict) const;

  /// @brief
  /// @param t
  /// @return
  Naive_Bool includesParameter(Naive_Real t) const;

  /// @brief
  /// @param t
  /// @param strict
  /// @return
  Naive_Bool includesParameter(Naive_Real t, Naive_Bool strict) const;

  /// @brief
  void makeIncreasing();

  /// @brief
  /// @param intervalParameter
  /// @return
  Interval normalizedIntervalAt(const Interval &intervalParameter) const;

  /// @brief
  /// @param intervalParameter
  /// @return
  Naive_Real normalizedParameterAt(Naive_Real intervalParameter) const;

  /// @brief
  /// @param normalizedParameter
  /// @return
  Naive_Real parameterAt(Naive_Real normalizedParameter) const;

  /// @brief
  /// @param normalizedInterval
  /// @return
  Interval parameterIntervalAt(const Interval &normalizedInterval) const;

  /// @brief Changes interval to [-T1, -T0].
  void reverse();

  /// @brief Exchanges T0 and T1.
  void swap();

public:
  Naive_Bool operator!=(const Interval &other) const;

  Naive_Bool operator<(const Interval &other) const;

  Naive_Bool operator<=(const Interval &other) const;

  Naive_Bool operator==(const Interval &other) const;

  Naive_Bool operator>(const Interval &other) const;

  Naive_Bool operator>=(const Interval &other) const;

  const Interval operator-(Naive_Real number) const;

  const Interval operator+(Naive_Real number) const;

  Interval &operator-=(Naive_Real number);

  Interval &operator+=(Naive_Real number);

private:
  Naive_Real m_t0;
  Naive_Real m_t1;
};

const Interval operator-(Naive_Real number, const Interval &interval);

const Interval operator+(Naive_Real number, const Interval &interval);

Naive_Namespace_End(geometry);

#endif
