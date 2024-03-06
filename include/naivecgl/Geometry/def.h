#ifndef _NaiveCGL_Geometry_def_HeaderFile
#define _NaiveCGL_Geometry_def_HeaderFile

#include <naivecgl/Common/def.h>

using Naive_Point2d = Naive_Vector2<Naive_Real>;
using Naive_Vector2d = Naive_Vector2<Naive_Real>;
using Naive_Point3d = Naive_Vector3<Naive_Real>;
using Naive_Vector3d = Naive_Vector3<Naive_Real>;
using Naive_Triangle = Naive_Vector3<Naive_Integer>;
using Naive_Point2d_List = Naive_List<Naive_Point2d>;
using Naive_Point3d_List = Naive_List<Naive_Point3d>;

#define Naive_VECTOR2D(V) Naive_Vector2d((V).x, (V).y)
#define Naive_VECTOR3D(V) Naive_Vector3d((V).x, (V).y, (V).z)
#define Naive_POINT2D(P) Naive_Vector2d((P).x, (P).y)
#define Naive_POINT3D(P) Naive_Vector3d((P).x, (P).y, (P).z)

#endif
