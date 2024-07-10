#include <naivecgl/Geometry/Line.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Line_new(const Naive_Line_sf_t *line_sf,
                            Naive_Line_t *const line) {
  if (!line_sf || !line)
    return Naive_Code_null_arg_address;

  Handle_Naive_Line aLine = new Naive_Line(*line_sf);
  Naive_ROSTER_ADD(aLine);
  *line = aLine->Tag();
  return Naive_Code_ok;
}
