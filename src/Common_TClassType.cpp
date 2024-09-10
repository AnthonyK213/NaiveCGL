/* clang-format off */
#include <naivecgl/Common/ClassType.h>
#include <naivecgl/Common/Object.h>
#include <naivecgl/Geometry2d/Geometry.h>
#include <naivecgl/Geometry2d/Point2d.h>
#include <naivecgl/Geometry2d/CartesianPoint2d.h>
#include <naivecgl/Geometry2d/Vector2d.h>
#include <naivecgl/Geometry2d/Curve.h>
#include <naivecgl/Geometry2d/BoundedCurve.h>
#include <naivecgl/Geometry2d/NurbsCurve.h>
#include <naivecgl/Geometry2d/TrimmedCurve.h>
#include <naivecgl/Geometry2d/Conic.h>
#include <naivecgl/Geometry2d/Circle.h>
#include <naivecgl/Geometry2d/Ellipse.h>
#include <naivecgl/Geometry2d/Hyperbola.h>
#include <naivecgl/Geometry2d/Parabola.h>
#include <naivecgl/Geometry2d/Line.h>
#include <naivecgl/Geometry2d/OffsetCurve.h>
#include <naivecgl/Geometry/Geometry.h>
#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/CartesianPoint3d.h>
#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Curve.h>
#include <naivecgl/Geometry/BoundedCurve.h>
#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Geometry/TrimmedCurve.h>
#include <naivecgl/Geometry/Conic.h>
#include <naivecgl/Geometry/Circle.h>
#include <naivecgl/Geometry/Ellipse.h>
#include <naivecgl/Geometry/Hyperbola.h>
#include <naivecgl/Geometry/Parabola.h>
#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Geometry/OffsetCurve.h>
#include <naivecgl/Geometry/Surface.h>
#include <naivecgl/Geometry/BoundedSurface.h>
#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Geometry/RectangularTrimmedSurface.h>
#include <naivecgl/Geometry/ElementarySurface.h>
#include <naivecgl/Geometry/ConicalSurface.h>
#include <naivecgl/Geometry/CylindricalSurface.h>
#include <naivecgl/Geometry/SphericalSurface.h>
#include <naivecgl/Geometry/ToroidalSurface.h>
#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Geometry/OffsetSurface.h>
#include <naivecgl/Geometry/Mesh.h>
#include <naivecgl/Geometry/Triangulation.h>

#include <naivecgl/BRep/PointRep.h>
#include <naivecgl/BRep/PointOnCurve.h>
#include <naivecgl/BRep/PointOnSurface.h>
#include <naivecgl/BRep/CurveRep.h>
#include <naivecgl/BRep/CurveOnSurface.h>

#include <naivecgl/Topology/Topol.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Solid.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>
/* clang-format on */

#include <naivecgl/Common/TClassType.h>

Naive_NAMESPACE_BEGIN(common);

TClassType::TClassType() : myClassType() {}

TClassType::TClassType(const Naive_Class theClass,
                       const Handle_Naive_ClassType &theClassType)
    : myClassType(theClassType) {
  if (myClassType)
    myClassType->myTag_ = static_cast<Naive_Tag>(theClass);
}

Naive_Class TClassType::GetClass() const {
  return myClassType ? static_cast<Naive_Class>(myClassType->myTag_)
                     : Naive_Class_null;
}

Naive_CStr TClassType::Name() const {
  return myClassType ? myClassType->Name() : "";
}

Naive_Size TClassType::Size() const {
  return myClassType ? myClassType->Size() : 0;
}

Naive_Class TClassType::Super() const {
  if (!myClassType)
    return Naive_Class_null;

  Handle_Naive_ClassType aSuper = myClassType->Super();
  return GetClass(aSuper);
}

Naive_Bool TClassType::IsSubClass(const Naive_Class theClass) const {
  return myClassType->IsSubClass(Resolve(theClass).GetClassType());
}

Naive_Class TClassType::GetClass(const Handle_Naive_ClassType &theClassType) {
  if (!theClassType)
    return Naive_Class_null;

  getRegistry();
  return static_cast<Naive_Class>(theClassType->myTag_);
}

TClassType TClassType::Resolve(const Naive_Class theClass) {
  const Registry &aRegistry = getRegistry();
  auto anIter = aRegistry.find(theClass);
  if (anIter != aRegistry.end())
    return anIter->second;
  return {};
}

#define Naive_CLASS_ENUM_PAIR(Class_, Enum_)                                   \
  {                                                                            \
    Enum_, { Enum_, Naive_CLASS(Class_) }                                      \
  }

const TClassType::Registry &TClassType::getRegistry() {
  static TClassType::Registry theRegistry{
      /* clang-format off */
      {Naive_Class_null, {}},
      Naive_CLASS_ENUM_PAIR(Naive_ClassType, Naive_Class_class),
      Naive_CLASS_ENUM_PAIR(Naive_Object, Naive_Class_object),
      Naive_CLASS_ENUM_PAIR(Naive_Geometry2d, Naive_Class_geometry2d),
      Naive_CLASS_ENUM_PAIR(Naive_Point2d, Naive_Class_point2d),
      Naive_CLASS_ENUM_PAIR(Naive_CartesianPoint2d, Naive_Class_cartesian_point2d),
      Naive_CLASS_ENUM_PAIR(Naive_Vector2d, Naive_Class_vector2d),
      Naive_CLASS_ENUM_PAIR(Naive_Curve2d, Naive_Class_curve2d),
      Naive_CLASS_ENUM_PAIR(Naive_BoundedCurve2d, Naive_Class_bounded_curve2d),
      Naive_CLASS_ENUM_PAIR(Naive_NurbsCurve2d, Naive_Class_nurbs_curve2d),
      Naive_CLASS_ENUM_PAIR(Naive_TrimmedCurve2d, Naive_Class_trimmed_curve2d),
      Naive_CLASS_ENUM_PAIR(Naive_Conic2d, Naive_Class_conic2d),
      Naive_CLASS_ENUM_PAIR(Naive_Circle2d, Naive_Class_circle2d),
      Naive_CLASS_ENUM_PAIR(Naive_Ellipse2d, Naive_Class_ellipse2d),
      Naive_CLASS_ENUM_PAIR(Naive_Hyperbola2d, Naive_Class_hyperbola2d),
      Naive_CLASS_ENUM_PAIR(Naive_Parabola2d, Naive_Class_parabola2d),
      Naive_CLASS_ENUM_PAIR(Naive_Line2d, Naive_Class_line2d),
      Naive_CLASS_ENUM_PAIR(Naive_OffsetCurve2d, Naive_Class_offset_curve2d),
      Naive_CLASS_ENUM_PAIR(Naive_Geometry, Naive_Class_geometry),
      Naive_CLASS_ENUM_PAIR(Naive_Point3d, Naive_Class_point3d),
      Naive_CLASS_ENUM_PAIR(Naive_CartesianPoint3d, Naive_Class_cartesian_point3d),
      Naive_CLASS_ENUM_PAIR(Naive_Vector3d, Naive_Class_vector3d),
      Naive_CLASS_ENUM_PAIR(Naive_Transform3d, Naive_Class_transform3d),
      Naive_CLASS_ENUM_PAIR(Naive_Curve, Naive_Class_curve),
      Naive_CLASS_ENUM_PAIR(Naive_BoundedCurve, Naive_Class_bounded_curve),
      Naive_CLASS_ENUM_PAIR(Naive_NurbsCurve, Naive_Class_nurbs_curve),
      Naive_CLASS_ENUM_PAIR(Naive_TrimmedCurve, Naive_Class_trimmed_curve),
      Naive_CLASS_ENUM_PAIR(Naive_Conic, Naive_Class_conic),
      Naive_CLASS_ENUM_PAIR(Naive_Circle, Naive_Class_circle),
      Naive_CLASS_ENUM_PAIR(Naive_Ellipse, Naive_Class_ellipse),
      Naive_CLASS_ENUM_PAIR(Naive_Hyperbola, Naive_Class_hyperbola),
      Naive_CLASS_ENUM_PAIR(Naive_Parabola, Naive_Class_parabola),
      Naive_CLASS_ENUM_PAIR(Naive_Line, Naive_Class_line),
      Naive_CLASS_ENUM_PAIR(Naive_OffsetCurve, Naive_Class_offset_curve),
      Naive_CLASS_ENUM_PAIR(Naive_Surface, Naive_Class_surface),
      Naive_CLASS_ENUM_PAIR(Naive_BoundedSurface, Naive_Class_bounded_surface),
      Naive_CLASS_ENUM_PAIR(Naive_NurbsSurface, Naive_Class_nurbs_surface),
      Naive_CLASS_ENUM_PAIR(Naive_RectangularTrimmedSurface, Naive_Class_rectangular_trimmed_surface),
      Naive_CLASS_ENUM_PAIR(Naive_ElementarySurface, Naive_Class_elementary_surface),
      Naive_CLASS_ENUM_PAIR(Naive_ConicalSurface, Naive_Class_conical_surface),
      Naive_CLASS_ENUM_PAIR(Naive_CylindricalSurface, Naive_Class_cylindrical_surface),
      Naive_CLASS_ENUM_PAIR(Naive_SphericalSurface, Naive_Class_spherical_surface),
      Naive_CLASS_ENUM_PAIR(Naive_ToroidalSurface, Naive_Class_toroidal_surface),
      Naive_CLASS_ENUM_PAIR(Naive_Plane, Naive_Class_plane),
      Naive_CLASS_ENUM_PAIR(Naive_OffsetSurface, Naive_Class_offset_surface),
      Naive_CLASS_ENUM_PAIR(Naive_Mesh, Naive_Class_mesh),
      Naive_CLASS_ENUM_PAIR(Naive_Triangulation, Naive_Class_triangulation),

      Naive_CLASS_ENUM_PAIR(brep::PointRep, Naive_Class_point_rep),
      Naive_CLASS_ENUM_PAIR(brep::PointOnCurve, Naive_Class_point_on_curve),
      Naive_CLASS_ENUM_PAIR(brep::PointOnSurface, Naive_Class_point_on_surface),
      Naive_CLASS_ENUM_PAIR(brep::CurveRep, Naive_Class_curve_rep),
      Naive_CLASS_ENUM_PAIR(brep::CurveOnSurface, Naive_Class_curve_on_surface),

      Naive_CLASS_ENUM_PAIR(Naive_Topol, Naive_Class_topol),
      Naive_CLASS_ENUM_PAIR(Naive_Body, Naive_Class_body),
      Naive_CLASS_ENUM_PAIR(Naive_Solid, Naive_Class_solid),
      Naive_CLASS_ENUM_PAIR(Naive_Shell, Naive_Class_shell),
      Naive_CLASS_ENUM_PAIR(Naive_Face, Naive_Class_face),
      Naive_CLASS_ENUM_PAIR(Naive_Loop, Naive_Class_loop),
      Naive_CLASS_ENUM_PAIR(Naive_Fin, Naive_Class_fin),
      Naive_CLASS_ENUM_PAIR(Naive_Edge, Naive_Class_edge),
      Naive_CLASS_ENUM_PAIR(Naive_Vertex, Naive_Class_vertex),
      /* clang-format on */
  };
  return theRegistry;
}

Naive_NAMESPACE_END(common);
