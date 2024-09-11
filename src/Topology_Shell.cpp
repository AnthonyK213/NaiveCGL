#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Shell);

Shell::Shell()
    : myRegion(nullptr), myVertex(nullptr), myFace(nullptr), myEdge(nullptr) {}

Naive_Topol *Shell::Parent() const { return myRegion; }

Naive_Region *Shell::ParentRegion() const { return myRegion; }

void Shell::GetBox(Naive_Box &theBox) {}

void Shell::SetParent(Naive_Topol *theParent) {
  myRegion = dynamic_cast<Naive_Region *>(theParent);
}

Naive_NAMESPACE_END(topology);
