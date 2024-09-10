#ifndef _NaiveCGL_Topology_Fin_HeaderFile
#define _NaiveCGL_Topology_Fin_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Loop;
class Edge;
class Vertex;

class Fin final : public Naive_Topol {
public:
  Naive_EXPORT Fin();

  Naive_EXPORT Naive_Handle<Loop> ParentLoop() const ;

  Naive_EXPORT Naive_Handle<Edge> ParentEdge() const ;

  Naive_EXPORT Naive_Handle<Vertex> GetVertex() const ;

  Naive_EXPORT Naive_Handle<Fin> Twin() const;

  Naive_EXPORT Naive_Handle<Fin> Prev() const;

  Naive_EXPORT Naive_Handle<Fin> Next() const;

  Naive_EXPORT Naive_Handle<Fin> Comp() const;

  Naive_DEFINE_RTTI(Fin, Naive_Topol);

private:
  Loop *myLoop;                /* Parent loop. */
  Naive_Handle<Edge> myEdge;   /* Parent edge. */
  Naive_Handle<Vertex> myVert; /* Forward vertex. */
  Naive_Handle<Fin> myTwin;    /* Next fin around myEdge. */
  Fin *myPrev;                 /* Previous fin in myLoop. */
  Fin *myNext;                 /* Next fin in myLoop. */
  Fin *myComp;                 /* Next fin around myVert. */
};

Naive_NAMESPACE_END(topology);

using Naive_Fin = ::naivecgl::topology::Fin;
Naive_DEFINE_HANDLE(Naive_Fin);

#endif
