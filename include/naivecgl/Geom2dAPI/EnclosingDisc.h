#ifndef _NaiveCGL_Geom2dAPI_EnclosingDisc_HeaderFile
#define _NaiveCGL_Geom2dAPI_EnclosingDisc_HeaderFile

#include "../Math/Pnt2d.h"

Naive_NAMESPACE_BEGIN(geom2dapi);

class EnclosingDisc final {
public:
  Naive_EXPORT EnclosingDisc();

  Naive_EXPORT void ReBuild(const Naive_Pnt2dList1 &thePoints);

  Naive_EXPORT Naive_Bool Result(Naive_Pnt2d &theOrigin,
                                 Naive_Real &theR) const;

  Naive_EXPORT const Naive_Pnt2dList1 &Points() const { return myPoints; }

private:
  Naive_Bool isInsideCircle(const Naive_Pnt2d &theP);

  void minDisc();

  void minDiscWithPoint(const Naive_Integer theI);

  void minDiscWith2Points(const Naive_Integer theI, const Naive_Integer theJ);

  void circle3Points(const Naive_Pnt2d &theA, const Naive_Pnt2d &theB,
                     const Naive_Pnt2d &theC);

private:
  Naive_Pnt2dList1 myPoints;
  Naive_Pnt2d myOrigin;
  Naive_Real myR;
};

Naive_NAMESPACE_END(geom2dapi);

#endif
