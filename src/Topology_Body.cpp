#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Body);

Body::Body()
    : myBody(nullptr), myPrev(nullptr), myNext(nullptr), myChild(nullptr),
      myRegion(nullptr), myEdge(nullptr), myVertex(nullptr) {}

Naive_Topol *Body::Parent() const { return myBody; }

Naive_Body *Body::ParentBody() const { return myBody; }

void Body::GetBox(Naive_Box &theBox) {}

void Body::SetParent(Naive_Topol *theParent) {
  myBody = dynamic_cast<Naive_Body *>(theParent);
}

Naive_NAMESPACE_END(topology);
