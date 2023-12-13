#include <naivecgl/Geometry/Interval.h>
#include <naivecgl/Math/Util.h>

Naive_Namespace_Begin(geometry);

Interval::Interval(Naive_Real t0, Naive_Real t1) : m_t0(t0), m_t1(t1) {}

const Interval &Interval::unset() noexcept {
  static Interval Interval_Unset{naivecgl::math::UnsetValue,
                                 naivecgl::math::UnsetValue};
  return Interval_Unset;
}

Naive_Bool Interval::isDecreasing() const { return m_t0 > m_t1; }

Naive_Bool Interval::isIncreasing() const { return m_t0 < m_t1; }

Naive_Bool Interval::isSingleton() const { return isValid() && m_t0 == m_t1; }

Naive_Bool Interval::isValid() const {
  return naivecgl::math::isValidDouble(m_t0) &&
         naivecgl::math::isValidDouble(m_t1);
}

Naive_Real Interval::length() const { return m_t1 - m_t0; }

Naive_Real Interval::max() const { return std::max(m_t0, m_t1); }

Naive_Real Interval::mid() const { return (m_t0 + m_t1) / 2.0; }

Naive_Real Interval::min() const { return std::min(m_t0, m_t1); }

Naive_Real Interval::t0() const { return m_t0; }

Naive_Real Interval::t1() const { return m_t1; }

Interval Interval::fromIntersection(const Interval &a, const Interval &b) {
  if (a.isValid() && b.isValid()) {
    Naive_Real min_ = std::max(a.min(), b.min());
    Naive_Real max_ = std::min(a.max(), b.max());

    if (min_ <= max_) {
      return Interval(min_, max_);
    }
  }

  return Interval::unset();
}

Interval Interval::fromUnion(const Interval &a, const Interval &b) {
  if (a.isValid() && b.isValid()) {
    Naive_Real min_ = std::min(a.min(), b.min());
    Naive_Real max_ = std::max(a.max(), b.max());

    return Interval(min_, max_);
  }

  return Interval::unset();
}

int32_t Interval::compareTo(const Interval &other) const {
  if (m_t0 < other.m_t0) {
    return -1;
  }

  if (m_t0 > other.m_t0) {
    return 1;
  }

  if (m_t1 < other.m_t1) {
    return -1;
  }

  if (m_t1 > other.m_t1) {
    return 1;
  }

  return 0;
}

Naive_Bool Interval::epsilonEquals(const Interval &other,
                                   Naive_Real epsilon) const {
  return naivecgl::math::epsilonEquals(m_t0, other.m_t0, epsilon) &&
         naivecgl::math::epsilonEquals(m_t1, other.m_t1, epsilon);
}

Naive_Bool Interval::equals(const Interval &other) const {
  return *this == other;
}

void Interval::grow(Naive_Real value) {
  if (isDecreasing()) {
    swap();
  }

  if (m_t0 > value) {
    m_t0 = value;
  }

  if (m_t1 < value) {
    m_t1 = value;
  }
}

Naive_Bool Interval::includesInterval(const Interval &interval) const {
  return includesInterval(interval, false);
}

Naive_Bool Interval::includesInterval(const Interval &interval,
                                      Naive_Bool strict) const {
  return includesParameter(interval.m_t0, strict) &&
         includesParameter(interval.m_t1, strict);
}

Naive_Bool Interval::includesParameter(Naive_Real t) const {
  return includesParameter(t, false);
}

Naive_Bool Interval::includesParameter(Naive_Real t, Naive_Bool strict) const {
  if (!naivecgl::math::isValidDouble(t)) {
    return false;
  }
  if (strict) {
    return (m_t0 <= m_t1 && m_t0 < t && t < m_t1) ||
           (m_t1 <= m_t0 && m_t1 < t && t < m_t0);
  } else {
    return (m_t0 <= m_t1 && m_t0 <= t && t <= m_t1) ||
           (m_t1 <= m_t0 && m_t1 <= t && t <= m_t0);
  }
}

void Interval::makeIncreasing() {
  if (isDecreasing()) {
    swap();
  }
}

Interval
Interval::normalizedIntervalAt(const Interval &intervalParameter) const {
  Naive_Real t = normalizedParameterAt(intervalParameter.m_t0);
  Naive_Real t2 = normalizedParameterAt(intervalParameter.m_t1);
  return Interval(t, t2);
}

Naive_Real Interval::normalizedParameterAt(Naive_Real intervalParameter) const {
  if (naivecgl::math::isValidDouble(intervalParameter)) {
    if (m_t0 != m_t1) {
      return (intervalParameter == m_t1)
                 ? 1.0
                 : ((intervalParameter - m_t0) / length());
    }

    return m_t0;
  }

  return naivecgl::math::UnsetValue;
}

Naive_Real Interval::parameterAt(Naive_Real normalizedParameter) const {
  if (!naivecgl::math::isValidDouble(normalizedParameter)) {
    return naivecgl::math::UnsetValue;
  }

  return (1.0 - normalizedParameter) * m_t0 + normalizedParameter * m_t1;
}

Interval
Interval::parameterIntervalAt(const Interval &normalizedInterval) const {
  Naive_Real t = parameterAt(normalizedInterval.m_t0);
  Naive_Real t2 = parameterAt(normalizedInterval.m_t1);

  return Interval(t, t2);
}

void Interval::reverse() {
  Naive_Real temp = m_t0;
  m_t0 = -m_t1;
  m_t1 = -temp;
}

void Interval::swap() { std::swap(m_t0, m_t1); }

Naive_Bool Interval::operator!=(const Interval &other) const {
  return compareTo(other) != 0;
}

Naive_Bool Interval::operator<(const Interval &other) const {
  return compareTo(other) < 0;
}

Naive_Bool Interval::operator<=(const Interval &other) const {
  return compareTo(other) <= 0;
}

Naive_Bool Interval::operator==(const Interval &other) const {
  return compareTo(other) == 0;
}

Naive_Bool Interval::operator>(const Interval &other) const {
  return compareTo(other) > 0;
}

Naive_Bool Interval::operator>=(const Interval &other) const {
  return compareTo(other) >= 0;
}

const Interval Interval::operator-(Naive_Real number) const {
  return Interval(m_t0 - number, m_t1 - number);
}

const Interval Interval::operator+(Naive_Real number) const {
  return Interval(m_t0 + number, m_t1 + number);
}

Interval &Interval::operator-=(Naive_Real number) {
  m_t0 -= number;
  m_t1 -= number;

  return *this;
}

Interval &Interval::operator+=(Naive_Real number) {
  m_t0 += number;
  m_t1 += number;

  return *this;
}

const Interval operator-(Naive_Real number, const Interval &interval) {
  return Interval(number - interval.t0(), number - interval.t1());
}

const Interval operator+(Naive_Real number, const Interval &interval) {
  return Interval(number + interval.t0(), number + interval.t1());
}

Naive_Namespace_End(geometry);
