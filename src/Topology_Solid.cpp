#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Solid);

Solid::Solid() : Naive_Topol() {}

Handle_Naive_Topol Solid::Parent() const { return myBody; }

Handle_Naive_Body Solid::ParentBody() const { return myBody; }

void Solid::GetBox(Naive_Box &theBox) {}

void Solid::SetParent(const Handle_Naive_Topol &theParent) {
  auto aBody = Handle_Naive_Body::DownCast(theParent);
  if (aBody)
    myBody = aBody.get();
}

Naive_NAMESPACE_END(topology);
