#ifndef _NaiveCGL_Tessellation_Sphere_HeaderFile
#define _NaiveCGL_Tessellation_Sphere_HeaderFile

#include "../Geometry/Triangulation.h"

Naive_NAMESPACE_BEGIN(tessellation);

class Sphere {
public:
  Naive_EXPORT static Handle_Naive_Poly UVSphere(const Naive_Pnt3d &theCenter,
                                                 const Naive_Real theRadius);

  Naive_EXPORT static Handle_Naive_Poly
  TetraSphere(const Naive_Pnt3d &theCenter, const Naive_Real theRadius,
              const Naive_Integer theLevel = 6);

  Naive_EXPORT static Handle_Naive_Poly
  OctaSphere(const Naive_Pnt3d &theCenter, const Naive_Real theRadius,
             const Naive_Integer theLevel = 6);

  Naive_EXPORT static Handle_Naive_Poly
  IcoShpere(const Naive_Pnt3d &theCenter, const Naive_Real theRadius,
            const Naive_Integer theLevel = 6);
};

Naive_NAMESPACE_END(tessellation);

#endif
