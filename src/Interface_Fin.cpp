#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Fin_ask_edge(Naive_Fin_t fin, Naive_Edge_t *const edge) {
  if (!edge)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Fin, fin, F);
  Handle_Naive_Edge anEdge = F->ParentEdge();
  Naive_ROSTER_ADD(anEdge, Naive_True, *edge);

  return Naive_Code_ok;
}

Naive_Code_t Naive_Fin_is_positive(Naive_Fin_t fin,
                                   Naive_Logical_t *const is_positive) {
  if (!is_positive)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Fin, fin, F);
  *is_positive = F->Sense();

  return Naive_Code_ok;
}
