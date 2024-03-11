#ifndef _NaiveCGL_Shape_TriangleSoup_HeaderFile
#define _NaiveCGL_Shape_TriangleSoup_HeaderFile

#include "def.h"

Naive_NAMESPACE_BEGIN(geometry);

class TriangleSoup : std::enable_shared_from_this<TriangleSoup> {
  using VertexList = Naive_List<Naive_Point3d>;
  using TriangleList = Naive_List<Naive_Triangle>;

public:
  Naive_EXPORT TriangleSoup();

  template <typename V, typename T,
            typename = Naive_WHERE_IS_REF_OF(V, VertexList),
            typename = Naive_WHERE_IS_REF_OF(T, TriangleList)>
  TriangleSoup(V &&theVertices, T &&theTriangles) {
    myVertices = std::forward<V>(theVertices);
    myTriangles = std::forward<T>(theTriangles);
  }

public:
  Naive_EXPORT Naive_Bool IsValid();

  Naive_EXPORT const VertexList &Vertices() const { return myVertices; }

  Naive_EXPORT const TriangleList &Triangles() const { return myTriangles; }

private:
  VertexList myVertices;
  TriangleList myTriangles;
};

Naive_NAMESPACE_END(geometry);

#endif
