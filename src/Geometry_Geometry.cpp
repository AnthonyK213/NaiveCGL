#include <naivecgl/Geometry/Geometry.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Geometry);

Naive_Code Geometry::Transform(const Naive_Trsf3d &theTrsf) {
  if (!theTrsf.IsValid())
    return Naive_Code_invalid_value;

  if (!theTrsf.IsIdentity())
    return transform(theTrsf);

  return Naive_Code_ok;
}

Handle_Naive_Geometry Geometry::Transformed(const Naive_Trsf3d &theTrsf) {
  Handle_Naive_Geometry aClone = Clone();
  if (!aClone || aClone->Transform(theTrsf) != Naive_Code_ok)
    return nullptr;
  return aClone;
}

Naive_NAMESPACE_END(geometry);
