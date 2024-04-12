#include <naivecgl/Math/Polynomial.h>

Naive_NAMESPACE_BEGIN(math);

Polynomial::Polynomial() : myA() {}

Polynomial::Polynomial(const Naive_RealList &theA) : myA(theA) {}

const Polynomial &Polynomial::Unset() {
  static Polynomial aP({});
  return aP;
}

const Polynomial &Polynomial::Zero() {
  static Polynomial aP({0.});
  return aP;
}

const Polynomial &Polynomial::Identity() {
  static Polynomial aP({1.});
  return aP;
}

Naive_Bool Polynomial::IsValid() const {
  if (Degree() < 0)
    return false;

  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    if (!Util::IsValidDouble(Coefficient(i)))
      return false;
  }

  return true;
}

Naive_Bool Polynomial::IsZero() const { return IsEqual(Zero()); }

Naive_Bool Polynomial::IsIdentity() const { return IsEqual(Identity()); }

Naive_Bool Polynomial::IsEqual(const Polynomial &theOther) const {
  if (!IsValid() || !theOther.IsValid())
    return false;

  if (Degree() != theOther.Degree())
    return false;

  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    // FIXME: Equality of float?
    if (Coefficient(i) != theOther.Coefficient(i))
      return false;
  }

  return true;
}

Naive_Integer Polynomial::Degree() const {
  return static_cast<Naive_Integer>(myA.size()) - 1;
}

Naive_Real Polynomial::Coefficient(const Naive_Integer theP) const {
  if (theP > Degree() || theP < 0)
    return 0;
  return myA[theP];
}

Naive_Real Polynomial::Evaluate(const Naive_Real theT) const {
  if (!IsValid())
    return Constant::UnsetValue();

  Naive_Real aRes = Coefficient(Degree());
  for (Naive_Integer i = Degree() - 1; i >= 0; --i) {
    aRes *= theT;
    aRes += Coefficient(i);
  }

  return aRes;
}

Polynomial Polynomial::Derivative(const Naive_Integer theN) const {
  if (!IsValid() || theN < 0)
    return Unset();

  if (Degree() <= theN - 1)
    return Zero();

  if (theN == 0)
    return *this;

  Naive_RealList a{};
  a.reserve(Degree() - theN + 1);

  for (Naive_Integer i = theN; i <= Degree(); ++i) {
    Naive_Integer k = i;
    for (Naive_Integer j = 1; j < theN; ++j) {
      k *= i - j;
    }
    a.push_back(myA[i] * static_cast<Naive_Real>(k));
  }

  return Polynomial(a);
}

void Polynomial::Negate() {
  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    myA[i] = -myA[i];
  }
}

Polynomial Polynomial::Negated() const {
  Polynomial aP{*this};
  aP.Negate();
  return aP;
}

void Polynomial::Add(const Polynomial &theOther) {
  Naive_Integer d = theOther.Degree();
  if (d > Degree())
    myA.resize(d + 1);
  else
    d = Degree();

  for (Naive_Integer i = 0; i <= d; ++i) {
    myA[i] += theOther.Coefficient(i);
  }
}

Polynomial Polynomial::Added(const Polynomial &theOther) const {
  Polynomial aP{*this};
  aP.Add(theOther);
  return aP;
}

void Polynomial::Subtract(const Polynomial &theOther) {
  Naive_Integer d = theOther.Degree();
  if (d > Degree())
    myA.resize(d + 1);
  else
    d = Degree();

  for (Naive_Integer i = 0; i <= d; ++i) {
    myA[i] -= theOther.Coefficient(i);
  }
}

Polynomial Polynomial::Subtracted(const Polynomial &theOther) const {
  Polynomial aP{*this};
  aP.Subtract(theOther);
  return aP;
}

void Polynomial::Multiply(const Naive_Real theT) {
  if (theT == 0.)
    myA = {0.};

  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    myA[i] *= theT;
  }
}

Polynomial Polynomial::Multiplied(const Naive_Real theT) const {
  if (theT == 0.)
    return Zero();
  Polynomial aP{*this};
  aP.Multiply(theT);
  return aP;
}

void Polynomial::Multiply(const Polynomial &theOther) {
  if (!IsValid() || !theOther.IsValid())
    return;

  Naive_RealList anA(Degree() + theOther.Degree() + 1, 0.0);
  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    for (Naive_Integer j = 0; j <= theOther.Degree(); ++j) {
      anA[i + j] += Coefficient(i) * theOther.Coefficient(j);
    }
  }

  ::std::swap(myA, anA);
}

Polynomial Polynomial::Multiplied(const Polynomial &theOther) const {
  if (!IsValid() || !theOther.IsValid())
    return Unset();
  Polynomial aP{*this};
  aP.Multiply(theOther);
  return aP;
}

Naive_Bool Polynomial::Divide(const Naive_Real theT) {
  if (!IsValid())
    return false;

  if (Util::EpsilonEquals(::std::abs(theT), Constant::ZeroTolerance()))
    return false;

  for (Naive_Integer i = 0; i <= Degree(); ++i) {
    myA[i] /= theT;
  }

  return true;
}

Polynomial Polynomial::Divided(const Naive_Real theT) const {
  Polynomial aP{*this};
  if (!aP.Divide(theT))
    return Unset();
  return aP;
}

Naive_Bool Polynomial::Divided(const Polynomial &theOther, Polynomial &theQ,
                               Polynomial &theR) const {
  if (theOther.Degree() > Degree() || !IsValid() || !theOther.IsValid())
    return false;
  // TODO: Divided by another polynomial.
  return true;
}

Naive_NAMESPACE_END(math);
