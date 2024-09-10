#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Vertex);

Vertex::Vertex()
    : Naive_Topol(), myTol(math::Precision::Epsilon0()), myPnt(nullptr) {}

Handle_Naive_Edge Vertex::ParentEdge() const {
  return Handle_Naive_Edge::DownCast(myParent);
}

Naive_Code Vertex::AttachPoint(const Handle_Naive_Point3d &aPoint) {
  if (myPnt)
    return Naive_Code_geom_not_needed;
  myPnt = aPoint;
  return Naive_Code_ok;
}

void Vertex::GetBox(Naive_Box &theBox) {
  if (myPnt)
    theBox = Naive_Box(myPnt->Pnt(), myPnt->Pnt());
}

Naive_NAMESPACE_END(topology);
