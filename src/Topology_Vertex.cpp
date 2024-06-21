#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Vertex::Vertex() : Naive_Topol() {}

Naive_Class Vertex::Class() const { return Naive_Class_vertex; }

Edge *Vertex::ParentEdge() const { return dynamic_cast<Edge *>(myParent); }

Naive_NAMESPACE_END(topology);
