#include <naivecgl/Geometry/TriangleSoup.h>

Naive_Namespace_Begin(geometry);

TriangleSoup::TriangleSoup() {}

TriangleSoup::TriangleSoup(TriangleSoup &&other) noexcept {
  m_vertices = std::move(other.m_vertices);
  m_triangles = std::move(other.m_triangles);
}

TriangleSoup::TriangleSoup(const VertexList &vertices,
                           const TriangleList &triangles) {
  m_vertices = vertices;
  m_triangles = triangles;
}

TriangleSoup::TriangleSoup(VertexList &&vertices, TriangleList &&triangles) {
  m_vertices = std::move(vertices);
  m_triangles = std::move(triangles);
}

TriangleSoup &TriangleSoup::operator=(TriangleSoup &&other) noexcept {
  m_vertices = std::move(other.m_vertices);
  m_triangles = std::move(other.m_triangles);

  return *this;
}

TriangleSoup::~TriangleSoup() {}

Naive_Bool TriangleSoup::isValid() {
  size_t nbVertices = m_vertices.size();

  for (const auto &triangle : m_triangles) {
    for (int i = 0; i < 3; ++i) {
      if (triangle(i) < 0 || triangle(i) >= nbVertices)
        return false;
    }
  }

  return true;
}

Naive_Namespace_End(geometry);
