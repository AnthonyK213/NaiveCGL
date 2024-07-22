#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Triangulation.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t
Naive_Triangulation_ask_triangles(const Naive_Triangulation_t triangulation,
                                  int *const n_triangles,
                                  Naive_Triangle_t **const triangles) {
  if (!n_triangles || !triangles)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Triangulation, triangulation, H);
  int nbTris = static_cast<int>(H->Triangles().size());

  *n_triangles = nbTris;

  Naive_ALLOC_ARRAY(Naive_Triangle_t, nbTris, triangles);
  for (Naive_Size i = 0; i < nbTris; ++i) {
    const Naive_Triangle &aTriangle = H->Triangles()[i];
    (*triangles)[i].n0 = aTriangle(0);
    (*triangles)[i].n1 = aTriangle(1);
    (*triangles)[i].n2 = aTriangle(2);
  }

  return Naive_Code_ok;
}

Naive_Code_t
Naive_Triangulation_ask_vertices(const Naive_Triangulation_t triangulation,
                                 int *const n_vertices,
                                 Naive_Point3d_t **const vertices) {
  if (!n_vertices || !vertices)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Triangulation, triangulation, H);
  int nbVerts = static_cast<int>(H->Vertices().size());

  *n_vertices = nbVerts;

  Naive_ALLOC_ARRAY(Naive_Point3d_t, nbVerts, vertices);
  for (Naive_Size i = 0; i < nbVerts; ++i) {
    H->Vertices()[i].Dump((*vertices)[i]);
  }

  return Naive_Code_ok;
}

Naive_Code_t
Naive_Triangulation_clone(const Naive_Triangulation_t triangulation,
                          Naive_Triangulation_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Triangulation, triangulation, H);
  Handle_Naive_Triangulation aClone = new Naive_Triangulation(*H);
  Naive_ROSTER_ADD(aClone, *clone);
  return Naive_Code_ok;
}

Naive_Code_t
Naive_Triangulation_is_valid(const Naive_Triangulation_t triangulation,
                             Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Triangulation, triangulation, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_Triangulation_new(const int n_vertices, const Naive_Point3d_t *vertices,
                        const int n_triangles,
                        const Naive_Triangle_t *triangles, const int i_offset,
                        Naive_Triangulation_t *const triangulation) {
  if (!vertices || !triangles || !triangulation)
    return Naive_Code_null_arg_address;

  if (n_vertices < 0 || n_triangles < 0)
    return Naive_Code_err;

  Naive_Pnt3dList1 aVerts(vertices, vertices + n_vertices);
  Naive_List1<Naive_Triangle> aTris(n_triangles);
  for (int i = 0; i < n_triangles; ++i) {
    aTris[i].x() = triangles[i].n0 - i_offset;
    aTris[i].y() = triangles[i].n1 - i_offset;
    aTris[i].z() = triangles[i].n2 - i_offset;
  }

  Handle_Naive_Triangulation aPoly =
      new Naive_Triangulation(::std::move(aVerts), ::std::move(aTris));
  Naive_ROSTER_ADD(aPoly, *triangulation);
  return Naive_Code_ok;
}
