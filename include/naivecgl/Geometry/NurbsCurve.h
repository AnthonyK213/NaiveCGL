#ifndef _NaiveCGL_Geometry_NurbsCurve_HeaderFile
#define _NaiveCGL_Geometry_NurbsCurve_HeaderFile

#include "Point3d.h"
#include "Vector3d.h"

#include <naivecgl/Common/Handle.h>

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve final : public Naive_Transient {
public:
  Naive_EXPORT NurbsCurve(const Naive_Point3dList &thePoles,
                          const Naive_RealList &theWeights,
                          const Naive_RealList &theKnots,
                          const Naive_IntegerList &theMults,
                          const Naive_Integer theDegree);

  Naive_EXPORT Naive_Integer Degree() const { return myDegree; }

  Naive_EXPORT Naive_Integer NbPoles() const;

  Naive_EXPORT const Naive_Point3d &Pole(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_Point3dList &Poles() const;

  Naive_EXPORT Naive_Real Weight(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_RealList &Weights() const;

  Naive_EXPORT Naive_Integer NbKnots() const;

  Naive_EXPORT Naive_Real Knot(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_RealList &Knots() const;

  Naive_EXPORT Naive_Real FirstParameter() const;

  Naive_EXPORT Naive_Real LastParameter() const;

  Naive_EXPORT Naive_Point3d PointAt(const Naive_Real theT) const;

  Naive_EXPORT Naive_Vector3d TangentAt(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool DerivativeAt(const Naive_Real theT,
                                       const Naive_Integer theN,
                                       Naive_Vector3dList &theD) const;

private:
  Naive_Bool isValid() const;

private:
  Naive_Bool myRational;
  Naive_Bool myPeriodic;
  Naive_Integer myDegree;
  Naive_Point3dList myPoles;
  Naive_RealList myWeights;
  Naive_RealList myFlatKnots;
  Naive_RealList myKnots;
  Naive_IntegerList myMults;
  Naive_IntegerList mySpanIdx;
};

Naive_NAMESPACE_END(geometry);

using Naive_NurbsCurve = ::naivecgl::geometry::NurbsCurve;
using Handle_Naive_NurbsCurve = Naive_Handle<Naive_NurbsCurve>;

#endif