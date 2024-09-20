#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Loop_ask_fins(Naive_Loop_t loop, int *const n_fins,
                                 Naive_Fin_t **const fins) {
  if (!n_fins)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Loop, loop, L);
  Naive_LinkedList<Handle_Naive_Fin> aFins = L->GetFins();
  *n_fins = static_cast<int>(aFins.size());

  if (fins) {
    Naive_unique_ptr<Naive_Fin_t> result;
    Naive_ALLOC_ARRAY(Naive_Fin_t, *n_fins, &result);
    int i = 0;
    for (const Handle_Naive_Fin &aFin : aFins) {
      Naive_ROSTER_ADD(aFin, Naive_True, result.get()[i++]);
    }
    *fins = result.release();
  }

  return Naive_Code_ok;
}
