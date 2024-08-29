#include <naivecgl/EulerOp/TEV.h>

Naive_NAMESPACE_BEGIN(eulerop);

TEV::TEV() noexcept : myVal() {}

TEV::TEV(Naive_Integer theV, Naive_Integer theE, Naive_Integer theF,
         Naive_Integer theH, Naive_Integer theG, Naive_Integer theB)
    : myVal() {
  myVal << theV, theE, theF, theH, theG, theB;
}

TEV::TEV(const Value &theVal) : myVal(theVal) {}

void TEV::Add(const TEV &theOther) { myVal += theOther.myVal; }

void TEV::Subtract(const TEV &theOther) { myVal -= theOther.myVal; }

TEV TEV::Added(const TEV &theOther) const {
  return TEV{myVal + theOther.myVal};
}

TEV TEV::Subtracted(const TEV &theOther) const {
  return TEV{myVal - theOther.myVal};
}

Naive_NAMESPACE_END(eulerop);
