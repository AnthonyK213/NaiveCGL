#ifndef _NaiveCGL_Topology_Fin_HeaderFile
#define _NaiveCGL_Topology_Fin_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Loop;
class Edge;
class Vertex;

class Fin final : public Naive_Topol {
  friend class Loop;
  friend class Edge;
  friend class eulerop::SplitEdge;

public:
  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Loop *ParentLoop() const;

  Naive_EXPORT Edge *ParentEdge() const;

  Naive_EXPORT const Naive_Handle<Vertex> &GetVertex() const;

  Naive_EXPORT const Naive_Handle<geometry::Curve> &GetCurve() const;

  Naive_EXPORT const Naive_Handle<Fin> &Twin() const;

  Naive_EXPORT Fin *Prev() const;

  Naive_EXPORT Fin *Next() const;

  Naive_EXPORT Fin *Comp() const;

  Naive_EXPORT Naive_Bool Sense() const;

  Naive_EXPORT Naive_Bool IsDummy() const;

  Naive_DEFINE_RTTI(Fin, Naive_Topol);

private:
  Naive_EXPORT Fin(const Naive_Handle<Edge> &theEdge,
                   const Naive_Handle<Vertex> &theVert, Naive_Bool theSense);

private:
  Loop *myLoop; /* Parent loop. */
  Edge *myEdge; /* Parent edge. */
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Handle<Vertex> myVert; /* Forward vertex. */
  Naive_Handle<Fin> myTwin;    /* Next fin around myEdge. */
  Fin *myPrev;                 /* Previous fin in myLoop. */
  Fin *myNext;                 /* Next fin in myLoop. */
  Fin *myComp;                 /* Next fin around myVert. */
  Naive_Bool mySense; /* True if the fin direction is parallel to myEdge. */
};

Naive_NAMESPACE_END(topology);

using Naive_Fin = ::naivecgl::topology::Fin;
Naive_DEFINE_HANDLE(Naive_Fin);

#endif
