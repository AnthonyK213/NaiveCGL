#ifndef _NaiveCGL_Shape_TriangleSoup_HeaderFile
#define _NaiveCGL_Shape_TriangleSoup_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export TriangleSoup {
  using VertexList = Naive_List<Naive_Vector3d>;
  using TriangleList = Naive_List<Naive_Triangle>;

public:
  TriangleSoup();

  TriangleSoup(TriangleSoup &&theOther) noexcept;

  TriangleSoup(const VertexList &theVertices, const TriangleList &theTriangles);

  TriangleSoup(VertexList &&theVertices, TriangleList &&theTriangles);

  TriangleSoup &operator=(TriangleSoup &&theOther) noexcept;

  ~TriangleSoup();

public:
  Naive_Bool IsValid();

  const VertexList &Vertices() const { return myVertices; }

  const TriangleList &Triangles() const { return myTriangles; }

private:
  VertexList myVertices{};
  TriangleList myTriangles{};
};

Naive_Namespace_End(geometry);

#endif
