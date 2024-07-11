#include <naivecgl/Geometry/Triangulation.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Poly_new(const int n_vertices,
                            const Naive_Point3d_t *vertices,
                            const int n_triangles,
                            const Naive_Triangle_t *triangles,
                            const int i_offset, Naive_Poly_t *const poly) {
  if (!vertices || !triangles || !poly)
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

  Handle_Naive_Poly aPoly =
      new Naive_Poly(::std::move(aVerts), ::std::move(aTris));
  Naive_ROSTER_ADD(aPoly);
  *poly = aPoly->Tag();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_is_valid(const Naive_Poly_t poly,
                                 Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Poly, poly, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_clone(const Naive_Poly_t poly,
                              Naive_Poly_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Poly, poly, H);
  Handle_Naive_Poly aClone = new Naive_Poly(*H);
  Naive_ROSTER_ADD(aClone);
  *clone = aClone->Tag();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_ask_vertices(const Naive_Poly_t poly,
                                     int *const n_vertices,
                                     Naive_Point3d_t *const vertices) {
  if (!n_vertices)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Poly, poly, H);
  int nbVerts = static_cast<int>(H->Vertices().size());
  *n_vertices = nbVerts;

  if (vertices) {
    for (Naive_Size i = 0; i < nbVerts; ++i) {
      H->Vertices()[i].Dump(vertices[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_ask_triangles(const Naive_Poly_t poly,
                                      int *const n_triangles,
                                      Naive_Triangle_t *const triangles) {
  if (!n_triangles)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Poly, poly, H);
  int nbTris = static_cast<int>(H->Triangles().size());
  *n_triangles = nbTris;

  if (triangles) {
    for (Naive_Size i = 0; i < nbTris; ++i) {
      const Naive_Triangle &aTriangle = H->Triangles()[i];
      triangles[i].n0 = aTriangle(0);
      triangles[i].n1 = aTriangle(1);
      triangles[i].n2 = aTriangle(2);
    }
  }

  return Naive_Code_ok;
}
