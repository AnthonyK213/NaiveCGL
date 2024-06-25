/// Reference: https://www.mdpi.com/2076-3417/10/2/655

#include <naivecgl/Tessellation/Sphere.h>

Naive_NAMESPACE_BEGIN(tessellation);

const Naive_Real SQRT_3 = ::std::sqrt(3.0);
const Naive_Real SQRT_1_3 = ::std::sqrt(1.0 / 3.0);

struct Vertex_ {
  Naive_XYZ myPoint;
  Naive_Integer myIndex;
};

static Naive_Integer triangle_index_(Naive_Integer theN, Naive_Integer theK) {
  return theK + ((theN * (theN + 1)) >> 1);
}

static Naive_Real tetra_tau_(const Naive_Real theU, const Naive_Real theV,
                             const Naive_Real theW) {
  Naive_Real u = theU * 0.5, v = theV * 0.5, w = theW * 0.5;
  Naive_Real Su = ::std::sin(u), Cu = ::std::cos(u);
  Naive_Real Sv = ::std::sin(v), Cv = ::std::cos(v);
  Naive_Real Sw = ::std::sin(w), Cw = ::std::cos(w);

  // clang-format off

  Naive_Matrix3d aMat{};
  aMat << SQRT_3 * Su,  -Cu,          -Cu,
          -Cv,          SQRT_3 * Sv,  -Cv,
          -Cw,          -Cw,          SQRT_3 * Sw;

  // clang-format on

  return aMat.determinant();
}

static Naive_Real tetra_xi_(const Naive_Real theU, const Naive_Real theV,
                            const Naive_Real theW) {
  Naive_Real u = theU * 0.5, v = theV * 0.5, w = theW * 0.5;
  Naive_Real Su = ::std::sin(u), Cu = ::std::cos(u);
  Naive_Real Sv = ::std::sin(v), Cv = ::std::cos(v);
  Naive_Real Sw = ::std::sin(w), Cw = ::std::cos(w);

  // clang-format off

  Naive_Matrix3d aMat{};
  aMat << Su,  Cu,            Cu,
          Sv,  -SQRT_3 * Sv,  Cv,
          Sw,  Cw,            -SQRT_3 * Sw;

  // clang-format on

  return aMat.determinant();
}

static void _tetra_t1(const Naive_Integer theD, const Naive_Integer theN,
                      const Naive_Integer theK, const Naive_Integer theI,
                      Vertex_ &theVertex) {
  Naive_Real l1 = Naive_Real(theD - theN - theK) / theD;
  Naive_Real l2 = Naive_Real(theN) / theD;
  Naive_Real l3 = Naive_Real(theK) / theD;

  Naive_Real t = tetra_tau_(l1, l2, l3);

  Naive_Real u = tetra_xi_(l1, l2, l3) / t;
  Naive_Real v = -tetra_xi_(l3, l2, l1) / t;
  Naive_Real w = -tetra_xi_(l2, l1, l3) / t;

  theVertex.myPoint = {u, v, w};
  theVertex.myIndex = theI;
}

static void _tetra_t2(const Naive_Integer theD, const Naive_Integer theN,
                      const Naive_Integer theK, const Naive_Integer theI,
                      Vertex_ &theVertex) {
  Naive_Real l2 = Naive_Real(theN + theK - 2 * theD) / theD;
  Naive_Real l1 = Naive_Real(theD - theN) / theD;
  Naive_Real l4 = Naive_Real(2 * theD - theK) / theD;

  Naive_Real t = tetra_tau_(l1, l2, l4);

  Naive_Real u = -tetra_xi_(l2, l1, l4) / t;
  Naive_Real v = -tetra_xi_(l4, l2, l1) / t;
  Naive_Real w = tetra_xi_(l1, l2, l4) / t;

  theVertex.myPoint = {u, v, w};
  theVertex.myIndex = theI;
}

static void _tetra_t3(const Naive_Integer theD, const Naive_Integer theN,
                      const Naive_Integer theK, const Naive_Integer theI,
                      Vertex_ &theVertex) {
  Naive_Real l1 = Naive_Real(theK - theD) / theD;
  Naive_Real l3 = Naive_Real(2 * theD - theN - theK) / theD;
  Naive_Real l4 = Naive_Real(theN) / theD;

  Naive_Real t = tetra_tau_(l1, l3, l4);

  Naive_Real u = -tetra_xi_(l3, l1, l4) / t;
  Naive_Real v = tetra_xi_(l1, l3, l4) / t;
  Naive_Real w = -tetra_xi_(l4, l3, l1) / t;

  theVertex.myPoint = {u, v, w};
  theVertex.myIndex = theI;
}

static void _tetra_t4(const Naive_Integer theD, const Naive_Integer theN,
                      const Naive_Integer theK, const Naive_Integer theI,
                      Vertex_ &theVertex) {
  Naive_Real l4 = Naive_Real(theN + theK - theD) / theD;
  Naive_Real l3 = Naive_Real(theD - theN) / theD;
  Naive_Real l2 = Naive_Real(theD - theK) / theD;

  Naive_Real t = tetra_tau_(l2, l3, l4);

  Naive_Real u = tetra_xi_(l4, l3, l2) / t;
  Naive_Real v = tetra_xi_(l2, l3, l4) / t;
  Naive_Real w = tetra_xi_(l3, l2, l4) / t;

  theVertex.myPoint = {u, v, w};
  theVertex.myIndex = theI;
}

static Naive_Integer _tetra_index(const Naive_Integer theD,
                                  const Naive_Integer theN,
                                  const Naive_Integer theK) {
  if ((theN == 0 || theN == theD) && theK > theD) {
    return 2 * theD - theK;
  }

  if (theK == 2 * theD) {
    return 0;
  }

  return theK;
}

Handle_Naive_Poly Sphere::UVSphere(const Naive_Pnt3d &theCenter,
                                   const Naive_Real theRadius) {
  Naive_TODO;
}

Handle_Naive_Poly Sphere::TetraSphere(const Naive_Pnt3d &theCenter,
                                      const Naive_Real theRadius,
                                      const Naive_Integer theLevel) {
  if (theRadius < 0 || theLevel < 0)
    return nullptr;

  Naive_List1<Naive_List1<Vertex_>> aVertices{};
  Naive_Integer d = theLevel + 1;

  aVertices.reserve(d + 1);

  Naive_Integer aVertIndex = 0;

  for (Naive_Integer n = 0; n <= d; ++n) {
    Naive_List1<Vertex_> aVerts{};

    if (n == 0) {
      aVerts.resize(d + 1);

      for (Naive_Integer k = 0; k <= d; ++k, ++aVertIndex) {
        _tetra_t1(d, n, k, aVertIndex, aVerts[k]);
      }
    } else if (n == d) {
      aVerts.resize(d + 1);

      for (Naive_Integer k = 0; k <= d; ++k, ++aVertIndex) {
        _tetra_t4(d, n, k, aVertIndex, aVerts[k]);
      }
    } else {
      aVerts.resize(2 * d);

      for (Naive_Integer k = 0; k < 2 * d; ++k, ++aVertIndex) {
        if (k <= d - n) {
          _tetra_t1(d, n, k, aVertIndex, aVerts[k]);
        } else if (k <= d) {
          _tetra_t4(d, n, k, aVertIndex, aVerts[k]);
        } else if (k <= 2 * d - n) {
          _tetra_t3(d, n, k, aVertIndex, aVerts[k]);
        } else {
          _tetra_t2(d, n, k, aVertIndex, aVerts[k]);
        }
      }
    }

    aVertices.push_back(::std::move(aVerts));
  }

  Naive_List1<Naive_Triangle> aTriangles{};
  aTriangles.reserve(4 * d * d);

  Naive_Integer i00, i10, i01, i11;

  for (Naive_Integer n = 0; n < d; ++n) {
    for (Naive_Integer k = 0; k < 2 * d; ++k) {
      i00 = _tetra_index(d, n, k);
      i10 = _tetra_index(d, n + 1, k);
      i01 = _tetra_index(d, n, k + 1);
      i11 = _tetra_index(d, n + 1, k + 1);

      aTriangles.push_back({
          aVertices[n][i00].myIndex,
          aVertices[n + 1][i10].myIndex,
          aVertices[n][i01].myIndex,
      });

      aTriangles.push_back({
          aVertices[n + 1][i10].myIndex,
          aVertices[n + 1][i11].myIndex,
          aVertices[n][i01].myIndex,
      });
    }
  }

  Naive_Pnt3dList1 aPoints{};
  aPoints.reserve(aVertIndex); // 2 * d * d + 2

  for (const auto &verts : aVertices) {
    for (const auto &vert : verts) {
      Naive_XYZ point = vert.myPoint;
      point.normalize();
      point *= theRadius;
      point += theCenter.XYZ();
      aPoints.push_back(point);
    }
  }

  return new Naive_Poly(::std::move(aPoints), ::std::move(aTriangles));
}

Handle_Naive_Poly Sphere::OctaSphere(const Naive_Pnt3d &theCenter,
                                     const Naive_Real theRadius,
                                     const Naive_Integer theLevel) {
  if (theRadius < 0 || theLevel < 0)
    return nullptr;

  Naive_List1<Naive_List1<Naive_XYZ>> aPoints{};
  Naive_Integer d = theLevel + 1;

  aPoints.reserve(d + 1);

  Naive_Real aHalf = theRadius * ::std::sqrt(0.5);
  Naive_XYZ aPntA{0.0, 0.0, theRadius};
  Naive_XYZ aPntB{aHalf, aHalf, 0.0};
  Naive_XYZ aPntC{-aHalf, aHalf, 0.0};

  for (Naive_Integer n = 0; n <= d; ++n) {
    Naive_List1<Naive_XYZ> aPnts{};
    aPnts.reserve(n + 1);

    Naive_Real a = Naive_Real(d - n) / d;

    for (Naive_Integer k = 0; k <= n; ++k) {
      Naive_Real b = Naive_Real(n - k) / d;
      Naive_Real c = Naive_Real(k) / d;

      aPnts.push_back(a * aPntA + b * aPntB + c * aPntC);

      aPnts[k].normalize();
      aPnts[k] *= theRadius;
      aPnts[k] += theCenter.XYZ();
    }

    aPoints.push_back(aPnts);
  }

  Naive_List1<Naive_Triangle> aTriangles{};
  aTriangles.reserve(d * d);

  for (Naive_Integer n = 1; n <= d; ++n) {
    aTriangles.push_back({triangle_index_(n, 0), triangle_index_(n, 1),
                          triangle_index_(n - 1, 0)});

    for (Naive_Integer k = 1; k < n; ++k) {
      aTriangles.push_back({triangle_index_(n, k), triangle_index_(n - 1, k),
                            triangle_index_(n - 1, k - 1)});
      aTriangles.push_back({triangle_index_(n, k), triangle_index_(n, k + 1),
                            triangle_index_(n - 1, k)});
    }
  }

  Naive_Pnt3dList1 aFlatPoints{};
  aFlatPoints.reserve(((d + 1) * (d + 2)) >> 1);

  for (Naive_Integer n = 0; n <= d; ++n) {
    for (Naive_Integer k = 0; k <= n; ++k) {
      aFlatPoints.push_back(aPoints[n][k]);
    }
  }

  return new Naive_Poly(::std::move(aFlatPoints), ::std::move(aTriangles));
}

Handle_Naive_Poly Sphere::IcoShpere(const Naive_Pnt3d &theCenter,
                                    const Naive_Real theRadius,
                                    const Naive_Integer theLevel) {
  Naive_TODO;
}

Naive_NAMESPACE_END(tessellation);
