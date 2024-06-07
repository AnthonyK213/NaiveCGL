#include <naivecgl/Geometry/TriangleSoup.h>

Naive_NAMESPACE_BEGIN(geometry);

TriangleSoup::TriangleSoup() : myVertices(), myTriangles() {}

Naive_Bool TriangleSoup::IsValid() const {
  Naive_Size nbVertices = myVertices.size();

  for (const Naive_Triangle &aTriangle : myTriangles) {
    for (Naive_Integer i = 0; i < 3; ++i) {
      if (aTriangle(i) < 0 || aTriangle(i) >= nbVertices)
        return Naive_False;
    }
  }

  return Naive_True;
}

Naive_NAMESPACE_END(geometry);
