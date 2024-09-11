#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Topol.h>
#include <naivecgl/Topology/Util.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Topol);

Topol::Topol() {}

Topol *Topol::Parent() const { return nullptr; }

Topol *Topol::TopTopol() const {
  Topol *aCurrent = const_cast<Topol *>(this);
  Topol *aParent = Parent();

  while (aParent) {
    aCurrent = aParent;
    aParent = aParent->Parent();
  }

  return aCurrent;
}

void Topol::GetBox(Naive_Box &theBox) {}

void Topol::SetParent(Naive_Topol *theParent) {}

Naive_NAMESPACE_END(topology);
