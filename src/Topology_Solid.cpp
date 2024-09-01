#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Solid);

Solid::Solid() : Naive_Topol() {}

Handle_Naive_Body Solid::ParentBody() const {
  return Handle_Naive_Body::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
