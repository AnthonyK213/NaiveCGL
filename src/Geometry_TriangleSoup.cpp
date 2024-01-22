#include <naivecgl/Geometry/TriangleSoup.h>

Naive_NAMESPACE_BEGIN(geometry);

TriangleSoup::TriangleSoup() : myVertices(), myTriangles() {}

TriangleSoup::TriangleSoup(TriangleSoup &&theOther) noexcept {
  myVertices = std::move(theOther.myVertices);
  myTriangles = std::move(theOther.myTriangles);
}

TriangleSoup &TriangleSoup::operator=(TriangleSoup &&theOther) noexcept {
  myVertices = std::move(theOther.myVertices);
  myTriangles = std::move(theOther.myTriangles);

  return *this;
}

TriangleSoup::~TriangleSoup() {}

Naive_Bool TriangleSoup::IsValid() {
  Naive_Size nbVertices = myVertices.size();

  for (const Naive_Triangle &aTriangle : myTriangles) {
    for (Naive_Integer i = 0; i < 3; ++i) {
      if (aTriangle(i) < 0 || aTriangle(i) >= nbVertices)
        return false;
    }
  }

  return true;
}

Naive_NAMESPACE_END(geometry);
