#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Math/Nurbs.h>

Naive_NAMESPACE_BEGIN(geometry);

template <typename T>
static Naive_Bool checkList2Bound(const Naive_List2<T> &theList2,
                                  Naive_Integer &theU, Naive_Integer &theV) {
  theU = static_cast<Naive_Integer>(theList2.size());
  if (theU == 0) {
    theV = 0;
    return true;
  }

  const Naive_List<T> &aList = theList2[0];
  theV = static_cast<Naive_Integer>(aList.size());
  for (Naive_Integer i = 1; i < theU; ++i) {
    if (theList2[i].size() != theV)
      return false;
  }

  return true;
}

NurbsSurface::NurbsSurface(
    const Naive_Point3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList &theUKnots, const Naive_RealList &theVKnots,
    const Naive_IntegerList &theUMults, const Naive_IntegerList &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree)
    : myURational(false), myVRational(false), myUPeriodic(false),
      myVPeriodic(false), myUDegree(0), myVDegree(0), myUFlatKnots(),
      myVFlatKnots() {
  if (theUDegree < 1 || theVDegree < 1)
    return;

  Naive_Integer aPU, aPV, aWU, aWV;
  if (!checkList2Bound(thePoles, aPU, aPV) ||
      !checkList2Bound(theWeights, aWU, aWV))
    return;

  if (aPU < 2 || aPV < 2)
    return;

  if (aPU != aWU || aPV != aWV)
    return;

  if (!math::Nurbs::CheckParam(aPU, theUKnots, theUMults, theUDegree,
                               myUPeriodic, myUFlatKnots, myUSpanIdx))
    return;

  if (!math::Nurbs::CheckParam(aPV, theVKnots, theVMults, theVDegree,
                               myVPeriodic, myVFlatKnots, myVSpanIdx))
    return;

  // TODO: Rational?

  myPoles = thePoles;
  myWeights = theWeights;
  myUKnots = theUKnots;
  myVKnots = theVKnots;
  myUMults = theUMults;
  myVMults = theVMults;
  myUDegree = theUDegree;
  myVDegree = theVDegree;
}

Naive_Bool NurbsSurface::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                Naive_Real &theV0, Naive_Real &theV1) const {
  return true;
}

Naive_Point3d NurbsSurface::PointAt(const Naive_Real theU,
                                    const Naive_Real theV) const {
  Naive_Vector3dList aD{};
  if (!Evaluate(theU, theV, 0, aD))
    return Naive_Point3d::Unset();
  return aD[0].XYZ();
}

Naive_Bool NurbsSurface::Evaluate(const Naive_Real theU, const Naive_Real theV,
                                  const Naive_Integer theN,
                                  Naive_Vector3dList &theD) const {
  if (!isValid())
    return false;

  Naive_Integer iUSpan = math::Nurbs::FindSpan(myUKnots, myUSpanIdx, theU);
  if (iUSpan < 0)
    return false;
  Naive_Integer iVSpan = math::Nurbs::FindSpan(myVKnots, myVSpanIdx, theV);
  if (iVSpan < 0)
    return false;

  Naive_IntegerList aHead(theN + 1, 0);
  for (Naive_Integer i = 1; i <= theN; ++i) {
    aHead[i] = aHead[i - 1] + i;
  }
  Naive_Integer aN = aHead[theN] + theN + 1;
  Naive_RealList2 aWBuf(theN + 1,
                        Naive_RealList(theN + 1, math::Constant::UnsetValue()));
  theD.resize(aN, Naive_Vector3d::Unset());
  Naive_List<math::Polynomial> anUA{};
  anUA.reserve(UDegree() + 1);
  Naive_List<math::Polynomial> anVA{};
  anVA.reserve(VDegree() + 1);
  Naive_Integer pUBegin = (::std::max)(0, iUSpan - UDegree());
  Naive_Integer pUEnd = iUSpan;
  Naive_Integer pVBegin = (::std::max)(0, iVSpan - VDegree());
  Naive_Integer pVEnd = iVSpan;
  for (Naive_Integer i = pUBegin; i <= pUEnd; ++i) {
    auto uB = math::Nurbs::BasisFn(myUFlatKnots, i, UDegree(), iUSpan);
    anUA.emplace_back(::std::move(uB));
  }
  for (Naive_Integer j = pVBegin; j <= pVEnd; ++j) {
    auto vB = math::Nurbs::BasisFn(myVFlatKnots, j, VDegree(), iVSpan);
    anVA.emplace_back(::std::move(vB));
  }

  for (Naive_Integer I = 0; I <= theN; ++I) {
    for (Naive_Integer L = 0; L <= I; ++L) {
      Naive_XYZ A{0., 0., 0.};
      Naive_Real W = 0.0;
      Naive_Integer K = I - L;
      for (Naive_Integer i = pUBegin; i <= pUEnd; ++i) {
        auto nU = anUA[i - pUBegin].Derivative(K).Evaluate(theU);
        for (Naive_Integer j = pVBegin; j <= pVEnd; ++j) {
          auto nV = anUA[j - pVBegin].Derivative(L).Evaluate(theV);
          Naive_Real N = nU * nV * myWeights[i][j];
          A += N * myPoles[i][j].XYZ();
          W += N;
        }
      }

      aWBuf[K][L] = W;

      for (Naive_Integer i = 1; i <= K; ++i) {
        A -= static_cast<Naive_Real>(math::Util::Combination(K, i)) *
             aWBuf[i][0] * theD[aHead[I - i] + L].XYZ();
      }

      for (Naive_Integer j = 1; j <= L; ++j) {
        A -= static_cast<Naive_Real>(math::Util::Combination(L, j)) *
             aWBuf[0][j] * theD[aHead[I - j] + L - j].XYZ();
      }

      for (Naive_Integer i = 1; i <= K; ++i) {
        Naive_XYZ M = {0., 0., 0.};
        for (Naive_Integer j = 1; j <= L; ++j) {
          M += static_cast<Naive_Real>(math::Util::Combination(L, j)) *
               aWBuf[i][j] * theD[aHead[I - i - j] + L - j].XYZ();
        }
        A -= static_cast<Naive_Real>(math::Util::Combination(K, i)) * M;
      }

      theD[aHead[I] + L].ChangeXYZ() = A / aWBuf[0][0];
    }
  }

  return true;
}

Naive_Bool NurbsSurface::isValid() const {
  return myUDegree > 0 && myVDegree > 0;
}

Naive_NAMESPACE_END(geometry);
