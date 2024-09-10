#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Topol.h>
#include <naivecgl/Topology/Util.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Topol);

Topol::Topol()
    : myParent(0), myFlags(0), myLocation(),
      myOrient(Naive_Orientation_forward_c) {}

Naive_Location Topol::Location() const { Naive_TODO; }

Naive_Orientation Topol::Orientation() const {
  Naive_Orientation anOri = myOrient;
  Topol *aParent = myParent;
  while (aParent) {
    anOri = Util::Compose(anOri, aParent->myOrient);
  }
  return anOri;
}

Naive_Handle<Topol> Topol::TopTopol() const {
  const Topol *aCurrent = this;
  Topol *aParent = myParent;
  while (aParent) {
    aCurrent = aParent;
    aParent = aParent->myParent;
  }
  return aCurrent;
}

void Topol::GetBox(Naive_Box &theBox) {}

Naive_NAMESPACE_END(topology);
