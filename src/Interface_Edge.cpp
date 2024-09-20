#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Edge_ask_vertices(Naive_Edge_t edge,
                                     Naive_Vertex_t vertices[2]) {
  Naive_ROSTER_ASK(Naive_Edge, edge, E);
  Naive_ROSTER_ADD(E->GetVertex(0), Naive_True, vertices[0]);
  Naive_ROSTER_ADD(E->GetVertex(1), Naive_True, vertices[1]);
  return Naive_Code_ok;
}
