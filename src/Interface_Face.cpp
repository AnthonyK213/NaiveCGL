#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Loop.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Face_ask_first_loop(Naive_Face_t face,
                                       Naive_Loop_t *const first_loop) {
  if (!first_loop)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Face, face, F);
  Handle_Naive_Loop aLoop = F->OuterLoop();
  Naive_ROSTER_ADD(aLoop, Naive_True, *first_loop);
  return Naive_Code_ok;
}
