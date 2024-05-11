#ifndef _NaiveCGL_Math_Polynomial_HeaderFile
#define _NaiveCGL_Math_Polynomial_HeaderFile

#include "Util.h"

Naive_NAMESPACE_BEGIN(math);

class Polynomial {
public:
  Naive_EXPORT Polynomial();

  Naive_EXPORT explicit Polynomial(const Naive_RealList &theA);

  Naive_EXPORT static const Polynomial &Unset();

  Naive_EXPORT static const Polynomial &Zero();

  Naive_EXPORT static const Polynomial &Identity();

  Naive_EXPORT Naive_Bool IsValid() const { return myIsValid; }

  Naive_EXPORT Naive_Bool IsZero() const;

  Naive_EXPORT Naive_Bool IsIdentity() const;

  Naive_EXPORT Naive_Bool IsEqual(const Polynomial &theOther) const;

  Naive_EXPORT Naive_Integer Degree() const;

  Naive_EXPORT Naive_Real Coefficient(const Naive_Integer theP) const;

  Naive_EXPORT Naive_Real Evaluate(const Naive_Real theT) const;

  Naive_EXPORT Polynomial Derivative(const Naive_Integer theN) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Polynomial Negated() const;

  Naive_EXPORT void Add(const Polynomial &theOther);

  Naive_EXPORT Polynomial Added(const Polynomial &theOther) const;

  Naive_EXPORT void Subtract(const Polynomial &theOther);

  Naive_EXPORT Polynomial Subtracted(const Polynomial &theOther) const;

  Naive_EXPORT void Multiply(const Naive_Real theT);

  Naive_EXPORT Polynomial Multiplied(const Naive_Real theT) const;

  Naive_EXPORT void Multiply(const Polynomial &theOther);

  Naive_EXPORT Polynomial Multiplied(const Polynomial &theOther) const;

  Naive_EXPORT void Divide(const Naive_Real theT);

  Naive_EXPORT Polynomial Divided(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool Divided(const Polynomial &theOther, Polynomial &theQ,
                                  Polynomial &theR) const;

private:
  void validate();

private:
  Naive_RealList myA;
  Naive_Bool myIsValid;
};

Naive_NAMESPACE_END(math);

#endif
