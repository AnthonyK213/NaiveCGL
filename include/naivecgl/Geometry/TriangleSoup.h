#ifndef _NaiveCGL_Shape_TriangleSoup_HeaderFile
#define _NaiveCGL_Shape_TriangleSoup_HeaderFile

#include "def.h"

Naive_NAMESPACE_BEGIN(geometry);

class TriangleSoup : std::enable_shared_from_this<TriangleSoup> {
  using VertexList = Naive_List<Naive_Vector3d>;
  using TriangleList = Naive_List<Naive_Triangle>;

public:
  Naive_EXPORT TriangleSoup();

  Naive_EXPORT TriangleSoup(TriangleSoup &&theOther) noexcept;

  Naive_EXPORT TriangleSoup(const VertexList &theVertices,
                            const TriangleList &theTriangles);

  Naive_EXPORT TriangleSoup(VertexList &&theVertices,
                            TriangleList &&theTriangles);

  Naive_EXPORT TriangleSoup &operator=(TriangleSoup &&theOther) noexcept;

  Naive_EXPORT ~TriangleSoup();

public:
  Naive_EXPORT Naive_Bool IsValid();

  const VertexList &Vertices() const { return myVertices; }

  const TriangleList &Triangles() const { return myTriangles; }

private:
  VertexList myVertices{};
  TriangleList myTriangles{};
};

Naive_NAMESPACE_END(geometry);

#endif
