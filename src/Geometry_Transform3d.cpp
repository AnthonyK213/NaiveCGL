#include <naivecgl/Geometry/Transform3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Transform3d::Transform3d() {}

Transform3d::Transform3d(const Naive_Trsf3d &theTrsf) : myTrsf(theTrsf) {}

Naive_Bool Transform3d::IsValid() const { return myTrsf.IsValid(); }

Naive_NAMESPACE_END(geometry);
