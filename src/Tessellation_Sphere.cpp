#include <naivecgl/Tessellation/Sphere.h>

namespace naivecgl {
namespace tessellation {

static Naive_Integer triangleIndex(Naive_Integer n, Naive_Integer k) {
  return k + ((n * (n + 1)) >> 1);
}

void uvsphere(const Naive_Vector3d &center, const Naive_Real radius,
              Naive_Poly3D &poly) {}

Naive_H_Poly3D octasphere(const Naive_Vector3d &center, const Naive_Real radius,
                          const Naive_Integer level) {
  if (radius < 0 || level < 0 || level > 10)
    return nullptr;

  std::vector<std::vector<Naive_Vector3d>> aPoints{};
  Naive_Integer d = ((2 << level) >> 1);

  aPoints.reserve(d + 1);

  Naive_Real aHalf = radius * std::sqrt(0.5);
  Naive_Vector3d aPntA{0.0, 0.0, aHalf};
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
    aTriangles.push_back(
        {triangleIndex(n, 0), triangleIndex(n, 1), triangleIndex(n - 1, 0)});

    for (Naive_Integer k = 1; k < n; ++k) {
      aTriangles.push_back({triangleIndex(n, k), triangleIndex(n - 1, k),
                            triangleIndex(n - 1, k - 1)});
      aTriangles.push_back({triangleIndex(n, k), triangleIndex(n, k + 1),
                            triangleIndex(n - 1, k)});
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

void icoshpere(const Naive_Vector3d &center, const Naive_Real radius,
               Naive_Poly3D &poly) {}

} // namespace tessellation
} // namespace naivecgl
