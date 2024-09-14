#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Vertex);

Vertex::Vertex()
    : myParent(nullptr), myFin(nullptr), myPrev(nullptr), myNext(nullptr),
      myPnt(nullptr), myTol(math::Precision::Epsilon0()) {}

Naive_Topol *Vertex::Parent() const { return myParent; }

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

Naive_Bool Vertex::IsManifold() const {
  /* TODO */
  return Naive_True;
}

void Vertex::SetParent(Naive_Topol *theParent) { myParent = theParent; }

Naive_NAMESPACE_END(topology);
