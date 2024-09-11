#ifndef _NaiveCGL_Topology_Body_HeaderFile
#define _NaiveCGL_Topology_Body_HeaderFile

#include "../Collection/LinkedList.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Region;
class Shell;
class Face;
class Edge;
class Vertex;

class Body final : public Naive_Topol {
  friend class eulerop::MakeBodyFaceVertex;

public:
  Naive_EXPORT Body();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Body *ParentBody() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Body, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Body *myBody;                  /* Parent body. */
  Body *myPrev;                  /* Previous body in myBody. */
  Naive_Handle<Body> myNext;     /* Next body in myBody. */
  Naive_Handle<Body> myChild;    /* Head of child bodies in the body. */
  Naive_Handle<Region> myRegion; /* Head of regions in the body. */
  Naive_Handle<Edge> myEdge;     /* Head of non-wireframe edges in the body. */
  Naive_Handle<Vertex> myVertex; /* Head of vertices in the body. */
};

Naive_NAMESPACE_END(topology);

using Naive_Body = ::naivecgl::topology::Body;
Naive_DEFINE_HANDLE(Naive_Body);

#endif
