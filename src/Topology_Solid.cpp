#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Solid::Solid() : Naive_Topol() {}

Naive_Class Solid::Class() const { return Naive_Class_solid; }

Handle_Naive_Body Solid::ParentBody() const {
  return Handle_Naive_Body::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
