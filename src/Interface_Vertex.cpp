#include "Interface_NaiveCGL_c.h"

#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Topology/Vertex.h>

Naive_Code_t Naive_Vertex_ask_point(Naive_Vertex_t vertex,
                                    Naive_Point_t *const point) {
  if (!point)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Vertex, vertex, V);
  Naive_ROSTER_ADD(V->GetPoint(), Naive_True, *point);
  return Naive_Code_ok;
}

Naive_Code_t Naive_Vertex_attach_points(int n_vertices,
                                        const Naive_Vertex_t vertices[],
                                        const Naive_Point_t points[]) {
  if (n_vertices < 0)
    return Naive_Code_insufficient_points;

  if (!vertices || !points)
    return Naive_Code_null_arg_address;

  for (int i = 0; i < n_vertices; ++i) {
    Naive_ROSTER_ASK(Naive_Vertex, vertices[i], HV);
    Naive_ROSTER_ASK(Naive_Point3d, points[i], HP);
    Naive_CHECK_CODE(HV->AttachPoint(HP));
  }

  return Naive_Code_not_implemented;
}
