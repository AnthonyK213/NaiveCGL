#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Loop);

Loop::Loop()
    : myFace(nullptr), myFin(nullptr), myType(Naive_Loop_type_outer_c) {}

Handle_Naive_Topol Loop::Parent() const { return myFace; }

Handle_Naive_Face Loop::ParentFace() const { return myFace; }

Naive_NAMESPACE_END(topology);
