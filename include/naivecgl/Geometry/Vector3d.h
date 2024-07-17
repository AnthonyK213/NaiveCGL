#ifndef _NaiveCGL_Geometry_Vector3d_HeaderFile
#define _NaiveCGL_Geometry_Vector3d_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Trsf3d.h"
#include "../Math/Vec3d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry);

class Vector3d final : public Naive_Geometry {
public:
  Naive_EXPORT Vector3d();

  Naive_EXPORT Vector3d(const Naive_Pnt3d &theP1, const Naive_Pnt3d &theP2);

  Naive_EXPORT Vector3d(const Naive_Real theX, const Naive_Real theY,
                        const Naive_Real theZ);

  Naive_EXPORT Vector3d(const Naive_Vec3d &theVec);

  Naive_EXPORT void SetVec(const Naive_Vec3d &theVec) { myVec = theVec; }

  Naive_EXPORT const Naive_Vec3d &Vec() const { return myVec; }

  Naive_EXPORT void SetX(const Naive_Real theX) { myVec.SetX(theX); }

  Naive_EXPORT void SetY(const Naive_Real theY) { myVec.SetY(theY); }

  Naive_EXPORT void SetZ(const Naive_Real theZ) { myVec.SetZ(theZ); }

  Naive_EXPORT Naive_Real X() const { return myVec.X(); }

  Naive_EXPORT Naive_Real Y() const { return myVec.Y(); }

  Naive_EXPORT Naive_Real Z() const { return myVec.Z(); }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Real Length() const;

  Naive_EXPORT Naive_Real SquareLength() const;

  Naive_EXPORT Naive_Bool Normalize();

  Naive_EXPORT Naive_Handle<Vector3d> Normalized() const;

  Naive_EXPORT void Add(const Naive_Handle<Vector3d> &theVec);

  Naive_EXPORT Naive_Handle<Vector3d>
  Added(const Naive_Handle<Vector3d> &theVec) const;

  Naive_EXPORT void Subtract(const Naive_Handle<Vector3d> &theVec);

  Naive_EXPORT Naive_Handle<Vector3d>
  Subtracted(const Naive_Handle<Vector3d> &theVec) const;

  Naive_EXPORT void Multiply(const Naive_Real theT);

  Naive_EXPORT Naive_Handle<Vector3d> Multiplied(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real theT);

  Naive_EXPORT Naive_Handle<Vector3d> Divided(const Naive_Real theT) const;

  Naive_EXPORT Naive_Real Dot(const Naive_Handle<Vector3d> &theVec) const;

  Naive_EXPORT void Cross(const Naive_Handle<Vector3d> &theVec);

  Naive_EXPORT Naive_Handle<Vector3d>
  Crossed(const Naive_Handle<Vector3d> &theVec) const;

  Naive_EXPORT void Reverse();

  Naive_EXPORT Naive_Handle<Vector3d> Reversed() const;

  Naive_EXPORT Naive_Bool Transform(const Naive_Trsf3d &theTrsf);

  Naive_DEFINE_RTTI(Vector3d, Naive_Geometry);

private:
  Naive_Vec3d myVec;
};

Naive_NAMESPACE_END(geometry);

using Naive_Vector3d = ::naivecgl::geometry::Vector3d;
Naive_DEFINE_HANDLE(Naive_Vector3d);
using Naive_Vector3dList1 = Naive_List1<Handle_Naive_Vector3d>;
using Naive_Vector3dList2 = Naive_List2<Handle_Naive_Vector3d>;

#endif
