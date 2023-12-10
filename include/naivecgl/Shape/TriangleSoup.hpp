#ifndef _NaiveCGL_Shape_TriangleSoup_Header
#define _NaiveCGL_Shape_TriangleSoup_Header

#include <naivecgl/Common/def.h>

namespace naivecgl {
namespace shape {

template <typename FloatType, typename IndexType> class TriangleSoup {
  using VertexList = std::vector<Naive_Vector3<FloatType>>;
  using TriangleList = std::vector<Naive_Vector3<IndexType>>;

public:
  TriangleSoup() {}

  TriangleSoup(VertexList &&vertices, TriangleList &&triangles) {
    m_vertices = std::move(vertices);
    m_triangles = std::move(triangles);
  }

  ~TriangleSoup() {}

public:
  bool isValid() {
    size_t nbVertices = m_vertices.size();

    for (const auto &triangle : m_triangles) {
      for (int i = 0; i < 3; ++i) {
        if (triangle(i) < 0 || triangle(i) >= nbVertices)
          return false;
      }
    }

    return true;
  }

  const VertexList &vertices() const { return m_vertices; }

  const TriangleList &triangles() const { return m_triangles; }

private:
  VertexList m_vertices{};

  TriangleList m_triangles{};
};

} // namespace shape
} // namespace naivecgl

#endif
