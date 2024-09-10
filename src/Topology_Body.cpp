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

Body::Body() : Naive_Topol() {}

void Body::GetBox(Naive_Box &theBox) {}

Naive_NAMESPACE_END(topology);
