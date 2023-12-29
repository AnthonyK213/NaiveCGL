#ifndef _NaiveCGL_Shape_TriangleSoup_HeaderFile
#define _NaiveCGL_Shape_TriangleSoup_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class TriangleSoup {
  using VertexList = Naive_List<Naive_Vector3d>;
  using TriangleList = Naive_List<Naive_Triangle>;

public:
  Naive_Export TriangleSoup();

  Naive_Export TriangleSoup(TriangleSoup &&theOther) noexcept;

  Naive_Export TriangleSoup(const VertexList &theVertices,
                            const TriangleList &theTriangles);

  Naive_Export TriangleSoup(VertexList &&theVertices,
                            TriangleList &&theTriangles);

  Naive_Export TriangleSoup &operator=(TriangleSoup &&theOther) noexcept;

  Naive_Export ~TriangleSoup();

public:
  Naive_Export Naive_Bool IsValid();

  const VertexList &Vertices() const { return myVertices; }

  const TriangleList &Triangles() const { return myTriangles; }

private:
  VertexList myVertices{};
  TriangleList myTriangles{};
};

Naive_Namespace_End(geometry);

#endif
