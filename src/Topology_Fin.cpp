#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Fin);

Fin::Fin() {}

Handle_Naive_Loop Fin::ParentLoop() const { return myLoop; }

Handle_Naive_Edge Fin::ParentEdge() const { return myEdge; }

Handle_Naive_Vertex Fin::GetVertex() const { return myVert; }

Handle_Naive_Fin Fin::Twin() const { return myTwin; }

Handle_Naive_Fin Fin::Prev() const { return myPrev; }

Handle_Naive_Fin Fin::Next() const { return myNext; }

Handle_Naive_Fin Fin::Comp() const { return myComp; }

Naive_NAMESPACE_END(topology);
