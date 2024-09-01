#ifndef _NaiveCGL_EulerOp_EOLib_HeaderFile
#define _NaiveCGL_EulerOp_EOLib_HeaderFile

#include "../Common/Handle.h"
#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "../Math/Eigen.h"

Naive_NAMESPACE_BEGIN(topology);

class Topol;

Naive_NAMESPACE_END(topology);

Naive_NAMESPACE_BEGIN(eulerop);

class TEV;

class EOLib {
public:
  Naive_EXPORT static Naive_Code
  GetTEV(const Naive_Handle<topology::Topol> &theTopol, TEV &theTEV);

  Naive_EXPORT static Naive_Code Resolve(const TEV &theDelta, TEV &theResult);

  Naive_EXPORT static Naive_Code Resolve(const TEV &theCurrent,
                                         const TEV &theTarget, TEV &theResult);

private:
  using TransfMat = ::Eigen::Matrix<Naive_Integer, 6, 6>;

  static const TransfMat &matA();

  static const TransfMat &invA();
};

Naive_NAMESPACE_END(eulerop);

#endif
