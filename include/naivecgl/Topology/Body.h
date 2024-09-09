#ifndef _NaiveCGL_Topology_Body_HeaderFile
#define _NaiveCGL_Topology_Body_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Math/Box.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Solid;
class Shell;
class Face;
class Edge;
class Vertex;

class Body final : public Naive_Topol {
  friend class eulerop::MakeBodyFaceVertex;

public:
  Naive_EXPORT Body();

  Naive_DEFINE_RTTI(Body, Naive_Topol);

protected:
  Naive_EXPORT virtual void UpdateBox(math::Box *theBox) Naive_OVERRIDE;

private:
  Naive_LinkedList<Naive_Handle<Body>> myBodies;
  Naive_LinkedList<Naive_Handle<Solid>> mySolids;
  Naive_LinkedList<Naive_Handle<Shell>> myShells;
  Naive_LinkedList<Naive_Handle<Face>> myFaces;
  Naive_LinkedList<Naive_Handle<Edge>> myEdges;
  Naive_LinkedList<Naive_Handle<Vertex>> myVertices;
  Naive_Box myBox;
};

Naive_NAMESPACE_END(topology);

using Naive_Body = ::naivecgl::topology::Body;
Naive_DEFINE_HANDLE(Naive_Body);

#endif
