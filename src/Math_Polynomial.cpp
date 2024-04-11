#include <naivecgl/Math/Polynomial.h>

Naive_NAMESPACE_BEGIN(math);

Polynomial::Polynomial(const Naive_RealList &theA) : myA(theA) {}

const Polynomial &Polynomial::Zero() {
  static Polynomial aP({});
  return aP;
}

Naive_Bool Polynomial::IsZero() const { return false; }

Naive_Integer Polynomial::Degree() const {
  return (::std::max)(static_cast<Naive_Integer>(myA.size()) - 1, 0);
}

Naive_Real Polynomial::Coefficient(const Naive_Integer theP) const {
  if (theP > Degree() || theP < 0)
    return 0;
  return myA[theP];
}

Naive_Real Polynomial::Evaluate(const Naive_Real theT) const {
  Naive_Real aRes = 0.;
  for (auto it = myA.crbegin(); it != myA.crend(); ++it) {
    aRes *= theT;
    aRes += *it;
  }
  return aRes;
}

Polynomial Polynomial::Derivative(const Naive_Integer theN) const {
  return Zero();
}

void Polynomial::Negate() {
  for (Naive_Real &a : myA) {
    a = -a;
  }
}

Polynomial Polynomial::Negated() const {
  Polynomial aP{*this};
  aP.Negate();
  return aP;
}

void Polynomial::Add(const Polynomial &theOther) {}

Polynomial Polynomial::Added(const Polynomial &theOther) const {
  return Zero();
}

void Polynomial::Subtract(const Polynomial &theOther) {}

Polynomial Polynomial::Subtracted(const Polynomial &theOther) const {
  return Zero();
}

void Polynomial::Multiply(const Naive_Real theT) {}

Polynomial Polynomial::Multiplied(const Naive_Real theT) const {
  return Zero();
}

void Polynomial::Multiply(const Polynomial &theOther) {}

Polynomial Polynomial::Multiplied(const Polynomial &theOther) const {
  return Zero();
}

void Polynomial::Divide(const Naive_Real theT) {}

Polynomial Polynomial::Divided(const Naive_Real theT) const { return Zero(); }

Naive_Bool Polynomial::Divided(const Polynomial &theOther, Polynomial &theQ,
                               Polynomial &theR) const {
  return true;
}

Naive_NAMESPACE_END(math);
