#ifndef _NaiveCGL_BndShape_EnclosingDisc_HeaderFile
#define _NaiveCGL_BndShape_EnclosingDisc_HeaderFile

#include <naivecgl/Geometry/Point2d.h>
#include <naivecgl/Geometry/Vector3d.h>

Naive_NAMESPACE_BEGIN(bndshape);

class EnclosingDisc final {
public:
  Naive_EXPORT EnclosingDisc();

  Naive_EXPORT void ReBuild(const Naive_Point2dList &thePoints);

  Naive_EXPORT Naive_Bool Circle(Naive_Point2d &theOrigin,
                                 Naive_Real &theR) const;

  Naive_EXPORT const Naive_Point2dList &Points() const { return myPoints; }

private:
  Naive_Bool isInsideCircle(const Naive_Point2d &theP);

  void minDisc();

  void minDiscWithPoint(const Naive_Integer theI);

  void minDiscWith2Points(const Naive_Integer theI, const Naive_Integer theJ);

  void circle3Points(const Naive_Point2d &theA, const Naive_Point2d &theB,
                     const Naive_Point2d &theC);

private:
  Naive_Point2dList myPoints;
  Naive_Point2d myOrigin;
  Naive_Real myR;
};

Naive_NAMESPACE_END(bndshape);

#endif
