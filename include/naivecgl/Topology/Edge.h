#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Math/Box.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Body;
class Fin;
class Vertex;

class Edge final : public Naive_Topol {
  friend class eulerop::SplitEdge;
  friend class eulerop::SpurEdgeVertex;
  friend class eulerop::MakeFaceEdge;

public:
  Naive_EXPORT Edge();

  Naive_EXPORT Edge(const Naive_Handle<Vertex> &theBackward,
                    const Naive_Handle<Vertex> &theForward);

  Naive_EXPORT virtual ~Edge();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT const Naive_Handle<Vertex> &GetVertex(Naive_Bool theForward);

  Naive_EXPORT const Naive_Handle<Fin> &ForwardFin() const;

  Naive_EXPORT const Naive_Handle<Fin> &BackwardFin() const;

  Naive_EXPORT Naive_LinkedList<Naive_Handle<Fin>>
  GetFins(const Naive_Bool theIncludeDummy = Naive_False) const;

  Naive_EXPORT const Naive_Handle<geometry::Curve> &GetCurve() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsManifold() const;

  Naive_DEFINE_RTTI(Edge, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Naive_EXPORT void init();

  Naive_EXPORT void setVertex(const Naive_Handle<Vertex> &theVert,
                              Naive_Bool theForward);

private:
  Naive_Topol *myParent;     /* Parent shell or body. */
  Edge *myPrev;              /* Previous edge in myParent. */
  Naive_Handle<Edge> myNext; /* Next edge in myParent. */
  Naive_Handle<Fin> myFin;   /* Head of fins around the edge. */
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Box myBox;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
