#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Region);

Region::Region()
    : myShells(), myBody(nullptr), myPrev(nullptr), myNext(nullptr) {}

Naive_Topol *Region::Parent() const { return myBody; }

Naive_Body *Region::ParentBody() const { return myBody; }

void Region::GetBox(Naive_Box &theBox) {}

void Region::SetParent(Naive_Topol *theParent) {
  myBody = dynamic_cast<Naive_Body *>(theParent);
}

Naive_NAMESPACE_END(topology);
