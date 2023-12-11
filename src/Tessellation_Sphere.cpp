/// Reference: https://www.mdpi.com/2076-3417/10/2/655

#include <naivecgl/Tessellation/Sphere.h>

namespace naivecgl {
namespace tessellation {

const Naive_Real SQRT_3 = std::sqrt(3.0);
const Naive_Real SQRT_1_3 = std::sqrt(1.0 / 3.0);

struct _Vertex_ {
  Naive_Vector3d m_point;
  Naive_Integer m_index;
};

static Naive_Integer _triangle_index_(Naive_Integer n, Naive_Integer k) {
  return k + ((n * (n + 1)) >> 1);
}

#define S ::std::sin
#define C ::std::cos

static Naive_Real _tetra_tau_(const Naive_Real u, const Naive_Real v,
                              const Naive_Real w) {
  // clang-format off

  Naive_Matrix3d aMat{};
  aMat << SQRT_3 * S(u * 0.5),  -C(u * 0.5),          -C(u * 0.5),
          -C(v * 0.5),          SQRT_3 * S(v * 0.5),  -C(v * 0.5),
          -C(w * 0.5),          -C(w * 0.5),          SQRT_3 * S(w * 0.5);

  // clang-format on

  return aMat.determinant();
}

static Naive_Real _tetra_xi_(const Naive_Real u, const Naive_Real v,
                             const Naive_Real w) {
  // clang-format off

  Naive_Matrix3d aMat{};
  aMat << S(u * 0.5),  C(u * 0.5),            C(u * 0.5),
          S(v * 0.5),  -SQRT_3 * S(v * 0.5),  C(v * 0.5),
          S(w * 0.5),  C(w * 0.5),            -SQRT_3 * S(w * 0.5);

  // clang-format on

  return aMat.determinant();
}

static void _tetra_t1(const Naive_Integer d, const Naive_Integer n,
                      const Naive_Integer k, const Naive_Integer i,
                      _Vertex_ &vertex) {
  Naive_Real l1 = Naive_Real(d - n - k) / d;
  Naive_Real l2 = Naive_Real(n) / d;
  Naive_Real l3 = Naive_Real(k) / d;

  Naive_Real t = _tetra_tau_(l1, l2, l3);

  Naive_Real u = _tetra_xi_(l1, l2, l3) / t;
  Naive_Real v = -_tetra_xi_(l3, l2, l1) / t;
  Naive_Real w = -_tetra_xi_(l2, l1, l3) / t;

  vertex.m_point = {u, v, w};
  vertex.m_index = i;
}

static void _tetra_t2(const Naive_Integer d, const Naive_Integer n,
                      const Naive_Integer k, const Naive_Integer i,
                      _Vertex_ &vertex) {
  Naive_Real l2 = Naive_Real(n + k - 2 * d) / d;
  Naive_Real l1 = Naive_Real(d - n) / d;
  Naive_Real l4 = Naive_Real(2 * d - k) / d;

  Naive_Real t = _tetra_tau_(l1, l2, l4);

  Naive_Real u = -_tetra_xi_(l2, l1, l4) / t;
  Naive_Real v = -_tetra_xi_(l4, l2, l1) / t;
  Naive_Real w = _tetra_xi_(l1, l2, l4) / t;

  vertex.m_point = {u, v, w};
  vertex.m_index = i;
}

static void _tetra_t3(const Naive_Integer d, const Naive_Integer n,
                      const Naive_Integer k, const Naive_Integer i,
                      _Vertex_ &vertex) {
  Naive_Real l1 = Naive_Real(k - d) / d;
  Naive_Real l3 = Naive_Real(2 * d - n - k) / d;
  Naive_Real l4 = Naive_Real(n) / d;

  Naive_Real t = _tetra_tau_(l1, l3, l4);

  Naive_Real u = -_tetra_xi_(l3, l1, l4) / t;
  Naive_Real v = _tetra_xi_(l1, l3, l4) / t;
  Naive_Real w = -_tetra_xi_(l4, l3, l1) / t;

  vertex.m_point = {u, v, w};
  vertex.m_index = i;
}

static void _tetra_t4(const Naive_Integer d, const Naive_Integer n,
                      const Naive_Integer k, const Naive_Integer i,
                      _Vertex_ &vertex) {
  Naive_Real l4 = Naive_Real(n + k - d) / d;
  Naive_Real l3 = Naive_Real(d - n) / d;
  Naive_Real l2 = Naive_Real(d - k) / d;

  Naive_Real t = _tetra_tau_(l2, l3, l4);

  Naive_Real u = _tetra_xi_(l4, l3, l2) / t;
  Naive_Real v = _tetra_xi_(l2, l3, l4) / t;
  Naive_Real w = _tetra_xi_(l3, l2, l4) / t;

  vertex.m_point = {u, v, w};
  vertex.m_index = i;
}

static Naive_Integer _tetra_index(const Naive_Integer d, const Naive_Integer n,
                                  const Naive_Integer k) {
  if ((n == 0 || n == d) && k > d) {
    return 2 * d - k;
  }

  if (k == 2 * d) {
    return 0;
  }

  return k;
}

#undef S
#undef C

void uvsphere(const Naive_Vector3d &center, const Naive_Real radius,
              Naive_Poly3D &poly) {}

Naive_H_Poly3D tetrasphere(const Naive_Vector3d &center,
                           const Naive_Real radius, const Naive_Integer level) {
  if (radius < 0 || level < 0)
    return nullptr;

  std::vector<std::vector<_Vertex_>> aVertices{};
  Naive_Integer d = level + 1;

  aVertices.reserve(d + 1);

  Naive_Integer aVertIndex = 0;

  for (Naive_Integer n = 0; n <= d; ++n) {
    std::vector<_Vertex_> aVerts{};

    if (n == 0) {
      aVerts.resize(d + 1);

      for (Naive_Integer k = 0; k <= d; ++k) {
        _tetra_t1(d, n, k, aVertIndex, aVerts[k]);
        aVertIndex++;
      }
    } else if (n == d) {
      aVerts.resize(d + 1);

      for (Naive_Integer k = 0; k <= d; ++k) {
        _tetra_t4(d, n, k, aVertIndex, aVerts[k]);
        aVertIndex++;
      }
    } else {
      aVerts.resize(2 * d);

      for (Naive_Integer k = 0; k < 2 * d; ++k) {
        if (k <= d - n) {
          _tetra_t1(d, n, k, aVertIndex, aVerts[k]);
        } else if (k <= d) {
          _tetra_t4(d, n, k, aVertIndex, aVerts[k]);
        } else if (k <= 2 * d - n) {
          _tetra_t3(d, n, k, aVertIndex, aVerts[k]);
        } else {
          _tetra_t2(d, n, k, aVertIndex, aVerts[k]);
        }

        aVertIndex++;
      }
    }

    aVertices.push_back(std::move(aVerts));
  }

  std::vector<Naive_Vector3i> aTriangles{};
  aTriangles.reserve(4 * d * d);

  for (Naive_Integer n = 0; n < d; ++n) {
    for (Naive_Integer k = 0; k < 2 * d; ++k) {
      aTriangles.push_back({
          aVertices[n][_tetra_index(d, n, k)].m_index,
          aVertices[n + 1][_tetra_index(d, n + 1, k)].m_index,
          aVertices[n][_tetra_index(d, n, k + 1)].m_index,
      });
      aTriangles.push_back({
          aVertices[n + 1][_tetra_index(d, n + 1, k)].m_index,
          aVertices[n + 1][_tetra_index(d, n + 1, k + 1)].m_index,
          aVertices[n][_tetra_index(d, n, k + 1)].m_index,
      });
    }
  }

  std::vector<Naive_Vector3d> aPoints{};
  aPoints.reserve(aVertIndex); // 2 * d * d + 2

  for (const auto &verts : aVertices) {
    for (const auto &vert : verts) {
      Naive_Vector3d point = vert.m_point;
      point.normalize();
      point *= radius;
      point += center;
      aPoints.push_back(point);
    }
  }

  return std::make_shared<Naive_Poly3D>(std::move(aPoints),
                                        std::move(aTriangles));
}

Naive_H_Poly3D octasphere(const Naive_Vector3d &center, const Naive_Real radius,
                          const Naive_Integer level) {
  if (radius < 0 || level < 0)
    return nullptr;

  std::vector<std::vector<Naive_Vector3d>> aPoints{};
  Naive_Integer d = level + 1;

  aPoints.reserve(d + 1);

  Naive_Real aHalf = radius * std::sqrt(0.5);
  Naive_Vector3d aPntA{0.0, 0.0, radius};
  Naive_Vector3d aPntB{aHalf, aHalf, 0.0};
  Naive_Vector3d aPntC{-aHalf, aHalf, 0.0};

  for (Naive_Integer n = 0; n <= d; ++n) {
    std::vector<Naive_Vector3d> aPnts{};
    aPnts.reserve(n + 1);

    Naive_Real a = Naive_Real(d - n) / d;

    for (Naive_Integer k = 0; k <= n; ++k) {
      Naive_Real b = Naive_Real(n - k) / d;
      Naive_Real c = Naive_Real(k) / d;

      aPnts.push_back(a * aPntA + b * aPntB + c * aPntC);

      aPnts[k].normalize();
      aPnts[k] *= radius;
      aPnts[k] += center;
    }

    aPoints.push_back(std::move(aPnts));
  }

  std::vector<Naive_Vector3i> aTriangles{};
  aTriangles.reserve(d * d);

  for (Naive_Integer n = 1; n <= d; ++n) {
    aTriangles.push_back({_triangle_index_(n, 0), _triangle_index_(n, 1),
                          _triangle_index_(n - 1, 0)});

    for (Naive_Integer k = 1; k < n; ++k) {
      aTriangles.push_back({_triangle_index_(n, k), _triangle_index_(n - 1, k),
                            _triangle_index_(n - 1, k - 1)});
      aTriangles.push_back({_triangle_index_(n, k), _triangle_index_(n, k + 1),
                            _triangle_index_(n - 1, k)});
    }
  }

  std::vector<Naive_Vector3d> aFlatPoints{};
  aFlatPoints.reserve(((d + 1) * (d + 2)) >> 1);

  for (Naive_Integer n = 0; n <= d; ++n) {
    for (Naive_Integer k = 0; k <= n; ++k) {
      aFlatPoints.push_back(aPoints[n][k]);
    }
  }

  return std::make_shared<Naive_Poly3D>(std::move(aFlatPoints),
                                        std::move(aTriangles));
}

Naive_H_Poly3D icoshpere(const Naive_Vector3d &center, const Naive_Real radius,
                         const Naive_Integer level) {
  return nullptr;
}

} // namespace tessellation
} // namespace naivecgl
