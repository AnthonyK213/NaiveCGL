#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Loop);

Loop::Loop() : Naive_Topol(), myType(Naive_Loop_type_outer_c) {}

Handle_Naive_Face Loop::ParentFace() const {
  return Handle_Naive_Face::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
