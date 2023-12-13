#ifndef _NaiveCGL_Shape_TriangleSoup_Header
#define _NaiveCGL_Shape_TriangleSoup_Header

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export TriangleSoup {
  using VertexList = Naive_List<Naive_Vector3d>;
  using TriangleList = Naive_List<Naive_Triangle>;

public:
  TriangleSoup();

  TriangleSoup(VertexList &&vertices, TriangleList &&triangles);

  ~TriangleSoup();

public:
  Naive_Bool isValid();

  const VertexList &vertices() const { return m_vertices; }

  const TriangleList &triangles() const { return m_triangles; }

private:
  VertexList m_vertices{};
  TriangleList m_triangles{};
};

Naive_Namespace_End(geometry);

#endif
