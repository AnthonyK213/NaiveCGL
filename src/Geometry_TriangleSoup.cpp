#include <naivecgl/Geometry/TriangleSoup.h>

Naive_Namespace_Begin(geometry);

TriangleSoup::TriangleSoup() {}

TriangleSoup::TriangleSoup(TriangleSoup &&theOther) noexcept {
  myVertices = std::move(theOther.myVertices);
  myTriangles = std::move(theOther.myTriangles);
}

TriangleSoup::TriangleSoup(const VertexList &theVertices,
                           const TriangleList &theTriangles) {
  myVertices = theVertices;
  myTriangles = theTriangles;
}

TriangleSoup::TriangleSoup(VertexList &&theVertices,
                           TriangleList &&theTriangles) {
  myVertices = std::move(theVertices);
  myTriangles = std::move(theTriangles);
}

TriangleSoup &TriangleSoup::operator=(TriangleSoup &&theOther) noexcept {
  myVertices = std::move(theOther.myVertices);
  myTriangles = std::move(theOther.myTriangles);

  return *this;
}

TriangleSoup::~TriangleSoup() {}

Naive_Bool TriangleSoup::IsValid() {
  size_t nbVertices = myVertices.size();

  for (const auto &aTriangle : myTriangles) {
    for (int i = 0; i < 3; ++i) {
      if (aTriangle(i) < 0 || aTriangle(i) >= nbVertices)
        return false;
    }
  }

  return true;
}

Naive_Namespace_End(geometry);
