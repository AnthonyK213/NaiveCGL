#ifndef _NaiveCGL_EulerOp_TEV_HeaderFile
#define _NaiveCGL_EulerOp_TEV_HeaderFile

#include <Eigen/Eigen>

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(euler_op);

/**
 * @brief Topological Element Vector:
 *
 */
class TEV final {
public:
  using Value = ::Eigen::Matrix<Naive_Integer, 6, 1>;

  Naive_EXPORT TEV() noexcept;

  Naive_EXPORT TEV(Naive_Integer theV, Naive_Integer theE, Naive_Integer theF,
                   Naive_Integer theH, Naive_Integer theG, Naive_Integer theB);

  Naive_EXPORT TEV(const Value &theVal);

  Naive_Integer V() const { return myVal[0]; }

  Naive_Integer E() const { return myVal[1]; }

  Naive_Integer F() const { return myVal[2]; }

  Naive_Integer H() const { return myVal[3]; }

  Naive_Integer G() const { return myVal[4]; }

  Naive_Integer B() const { return myVal[5]; }

  void SetV(Naive_Integer theVal) { myVal[0] = theVal; }

  void SetE(Naive_Integer theVal) { myVal[1] = theVal; }

  void SetF(Naive_Integer theVal) { myVal[2] = theVal; }

  void SetH(Naive_Integer theVal) { myVal[3] = theVal; }

  void SetG(Naive_Integer theVal) { myVal[4] = theVal; }

  void SetB(Naive_Integer theVal) { myVal[5] = theVal; }

  void Set(const Value &theVal) { myVal = theVal; }

  const Value &GetValue() const { return myVal; }

  Value &ChangeValue() { return myVal; }

  Naive_EXPORT void Add(const TEV &theOther);

  Naive_EXPORT void Subtract(const TEV &theOther);

  Naive_EXPORT TEV Added(const TEV &theOther) const;

  Naive_EXPORT TEV Subtracted(const TEV &theOther) const;

private:
  Value myVal;
};

Naive_NAMESPACE_END(euler_op);

#endif
