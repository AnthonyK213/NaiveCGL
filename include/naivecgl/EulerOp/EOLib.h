#ifndef _NaiveCGL_EulerOp_EOLib_HeaderFile
#define _NaiveCGL_EulerOp_EOLib_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

#include "TEV.h"

Naive_NAMESPACE_BEGIN(eulerop);

class EOLib {
public:
  Naive_EXPORT static Naive_Code Resolve(const TEV &theDelta, TEV &theResult);

  Naive_EXPORT static Naive_Code Resolve(const TEV &theCurrent,
                                         const TEV &theTarget, TEV &theResult);

private:
  using TransfMat = ::Eigen::Matrix<Naive_Integer, 6, 6>;

  Naive_EXPORT static const TransfMat &A();

  Naive_EXPORT static const TransfMat &InvA();
};

Naive_NAMESPACE_END(eulerop);

#endif
