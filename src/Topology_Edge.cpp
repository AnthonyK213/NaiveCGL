#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>

Naive_NAMESPACE_BEGIN(topology);

Edge::Edge() : Naive_Topol() {}

Naive_Class Edge::Class() const { return Naive_Class_edge; }

Fin *Edge::ParentFin() const { return dynamic_cast<Fin *>(myParent); }

Naive_NAMESPACE_END(topology);
