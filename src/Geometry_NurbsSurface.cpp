#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(NurbsSurface);

NurbsSurface::NurbsSurface() noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False), myUFlatKnots(), myVFlatKnots() {}

NurbsSurface::NurbsSurface(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree) noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False), myUFlatKnots(), myVFlatKnots() {
  Init(thePoles, theWeights, theUKnots, theVKnots, theUMults, theVMults,
       theUDegree, theVDegree);
}

Naive_Code NurbsSurface::Init(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree) noexcept {
  return update(thePoles, theWeights, theUKnots, theVKnots, theUMults,
                theVMults, theUDegree, theVDegree);
}

Naive_Bool NurbsSurface::IsValid() const {
  return myUDegree > 0 && myVDegree > 0;
}

Handle_Naive_Geometry NurbsSurface::Clone() const {
  return new NurbsSurface(*this);
}

Naive_Bool NurbsSurface::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                Naive_Real &theV0, Naive_Real &theV1) const {
  if (!IsValid())
    return Naive_False;

  theU0 = myUKnots[0];
  theU1 = myUKnots[myUKnots.size() - 1];
  theV0 = myVKnots[0];
  theV1 = myVKnots[myVKnots.size() - 1];

  return Naive_True;
}

Naive_Code NurbsSurface::Evaluate(const Naive_Real theU, const Naive_Real theV,
                                  const Naive_Integer theN,
                                  Naive_Vec3dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  Naive_Integer iUSpan = math::Nurbs::FindFlatSpan(myUKnots, myUSpanIdx, theU);
  if (iUSpan < 0)
    return Naive_Code_value_out_of_range;
  Naive_Integer iVSpan = math::Nurbs::FindFlatSpan(myVKnots, myVSpanIdx, theV);
  if (iVSpan < 0)
    return Naive_Code_value_out_of_range;

  Naive_IntegerList1 aHead(theN + 1, 0);
  for (Naive_Integer i = 1; i <= theN; ++i) {
    aHead[i] = aHead[i - 1] + i;
  }
  Naive_Integer aN = aHead[theN] + theN + 1;
  Naive_RealList2 aWBuf(theN + 1,
                        Naive_RealList1(theN + 1, math::Constant::UnsetReal()));
  theD.resize(aN, Naive_Vec3d::Unset());
  Naive_List1<math::Polynomial> anUA{};
  anUA.reserve(UDegree() + 1);
  Naive_List1<math::Polynomial> anVA{};
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
        Naive_Real nU = anUA[i - pUBegin].Derivative(K).Evaluate(theU);
        for (Naive_Integer j = pVBegin; j <= pVEnd; ++j) {
          Naive_Real nV = anUA[j - pVBegin].Derivative(L).Evaluate(theV);
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

  return Naive_Code_ok;
}

Naive_Code NurbsSurface::transform(const Naive_Trsf3d &theTrsf) {
  for (Naive_Pnt3dList1 &v : myPoles) {
    for (Naive_Pnt3d &p : v) {
      p.Transform(theTrsf);
    }
  }

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
