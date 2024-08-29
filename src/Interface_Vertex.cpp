#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Vertex_attach_points(int n_vertices,
                                        const Naive_Vertex_t vertices[],
                                        const Naive_Pnt3d_t points[]) {
  if (n_vertices < 0)
    return Naive_Code_insufficient_points;

  if (!vertices || !points)
    return Naive_Code_null_arg_address;

  return Naive_Code_not_implemented;
}
