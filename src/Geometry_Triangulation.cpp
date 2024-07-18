#include <naivecgl/Geometry/Triangulation.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Triangulation);

Triangulation::Triangulation() : myVertices(), myTriangles() {}

Naive_Bool Triangulation::IsValid() const {
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
