#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Body);

Body::Body() {}

Handle_Naive_Topol Body::Parent() const { return myParent; }

Handle_Naive_Body Body::ParentBody() const { return myParent; }

void Body::GetBox(Naive_Box &theBox) {}

void Body::SetParent(const Handle_Naive_Topol &theParent) {
  auto aBody = Handle_Naive_Body::DownCast(theParent);
  if (aBody)
    myParent = aBody.get();
}

Naive_NAMESPACE_END(topology);
