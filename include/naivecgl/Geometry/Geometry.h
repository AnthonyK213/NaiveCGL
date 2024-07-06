#ifndef _NaiveCGL_Geometry_Geometry_HeaderFile
#define _NaiveCGL_Geometry_Geometry_HeaderFile

#include "../Common/TObject.h"

Naive_NAMESPACE_BEGIN(geometry);

class Geometry : public Naive_TObject {
public:
  Naive_EXPORT virtual Naive_Bool IsValid() const = 0;

  Naive_EXPORT virtual Naive_Handle<Geometry> Clone() const = 0;

  // Naive_EXPORT virtual Naive_Bool
  // Transform(const Naive_Trsf3d &theTrsf) = 0;

  // Naive_EXPORT virtual Naive_Handle<Geometry>
  // Transformed(const Naive_Trsf3d &theTrsf) = 0;
};

Naive_NAMESPACE_END(geometry);

using Naive_Geometry = ::naivecgl::geometry::Geometry;
Naive_DEFINE_HANDLE(Naive_Geometry);

#endif
