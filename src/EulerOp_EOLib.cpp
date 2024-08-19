#include <naivecgl/EulerOp/EOLib.h>

Naive_NAMESPACE_BEGIN(eulerop);

Naive_Code EOLib::Resolve(const TEV &theDelta, TEV &theResult) {
  TEV aRes = InvA() * theDelta;
  theResult = aRes / 12;
  return Naive_Code_ok;
}

Naive_Code EOLib::Resolve(const TEV &theCurrent, const TEV &theTarget,
                          TEV &theResult) {
  return Resolve(theTarget - theCurrent, theResult);
}

const EOLib::TransfMat &EOLib::A() {
  /* clang-format off */
  static EOLib::TransfMat m = (EOLib::TransfMat() <<
    1,  0,  1,  0,  0,  1,
    1,  1,  0,  0,  1, -1,
    0,  1,  1,  0,  0,  1,
    0,  0,  0,  0, -1, -1,
    0,  0,  0,  1,  0,  2,
    0,  0,  1,  1,  0, -2
  ).finished();
  /* clang-format on */
  return m;
}

const EOLib::TransfMat &EOLib::InvA() {
  /* clang-format off */
  static EOLib::TransfMat m = (EOLib::TransfMat() <<
    7,  5, -5,  5,  2, -2,
   -5,  5,  7,  5,  2, -2,
    4, -4,  4, -4, -4,  4,
   -2,  2, -2,  2,  8,  4,
   -1,  1, -1,-11, -2,  2,
    1, -1,  1, -1,  2, -2
  ).finished();
  /* clang-format on */
  return m;
}

Naive_NAMESPACE_END(eulerop);
