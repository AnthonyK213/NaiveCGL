#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Loop.h>

Naive_NAMESPACE_BEGIN(topology);

Loop::Loop() : Naive_Topol() {}

Naive_Class Loop::Class() const { return Naive_Class_loop; }

Face *Loop::ParentFace() const { return dynamic_cast<Face *>(myParent); }

Naive_NAMESPACE_END(topology);
