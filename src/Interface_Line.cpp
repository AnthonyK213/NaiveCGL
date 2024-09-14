#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Line.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Line_ask(Naive_Line_t line, Naive_Line_sf_t *const line_sf) {
  if (!line_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Line, line, H);
  return H->Dump(*line_sf);
}

Naive_Code_t Naive_Line_create(const Naive_Line_sf_t *line_sf,
                               Naive_Line_t *const line) {
  if (!line_sf || !line)
    return Naive_Code_null_arg_address;

  Handle_Naive_Line aLine = new Naive_Line(*line_sf);
  Naive_ROSTER_ADD(aLine, Naive_True, *line);
  return Naive_Code_ok;
}
