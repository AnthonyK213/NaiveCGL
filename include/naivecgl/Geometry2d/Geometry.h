#ifndef _NaiveCGL_Geometry2d_Geometry_HeaderFile
#define _NaiveCGL_Geometry2d_Geometry_HeaderFile

#include "../Common/ClassType.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Geometry : public Naive_Object {
public:
  Naive_EXPORT virtual Naive_Bool IsValid() const = 0;

  Naive_EXPORT virtual Naive_Handle<Geometry> Clone() const = 0;

  Naive_DEFINE_RTTI(Geometry, Naive_Object, Naive_Class_geometry2d);
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Geometry2d = ::naivecgl::geometry2d::Geometry;
Naive_DEFINE_HANDLE(Naive_Geometry2d);

#endif
