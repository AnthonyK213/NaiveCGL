#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Topol.h>
#include <naivecgl/Topology/Util.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Topol);

Topol::Topol() {}

Handle_Naive_Topol Topol::Parent() const { return nullptr; }

Naive_Handle<Topol> Topol::TopTopol() const {
  const Topol *aCurrent = this;
  Topol *aParent = Parent().get();

  while (aParent) {
    aCurrent = aParent;
    aParent = aParent->Parent().get();
  }

  return aCurrent;
}

void Topol::GetBox(Naive_Box &theBox) {}

void Topol::SetParent(const Naive_Handle<Topol> &theParent) {}

Naive_NAMESPACE_END(topology);
