#ifndef _NaiveCGL_Geometry_Geometry_HeaderFile
#define _NaiveCGL_Geometry_Geometry_HeaderFile

#include "../Common/ClassType.h"

Naive_NAMESPACE_BEGIN(math);

class Trsf3d;

Naive_NAMESPACE_END(math);

Naive_NAMESPACE_BEGIN(geometry);

class Geometry : public Naive_Object {
public:
  /**
   * @brief Check if the geometry is valid.
   *
   * @return True if geometry is valid; otherwise, false.
   */
  Naive_EXPORT virtual Naive_Bool IsValid() const = 0;

  /**
   * @brief Make a deep copy of the geometry.
   *
   * @return The deep copy.
   */
  Naive_EXPORT virtual Naive_Handle<Geometry> Clone() const = 0;

  /**
   * @brief Transform the geometry with a transformation.
   *
   * @param theTrsf The transformation.
   * @return Code.
   */
  Naive_EXPORT Naive_Code Transform(const math::Trsf3d &theTrsf);

  /**
   * @brief Make a deep copy and transform.
   *
   * @param theTrsf The transformation.
   * @return Code.
   */
  Naive_EXPORT Naive_Handle<Geometry> Transformed(const math::Trsf3d &theTrsf);

  /**
   * @brief Get the owner object.
   *
   * @return The owner object.
   */
  const Handle_Naive_Object &GetOwner() const { return myOwner; }

  /**
   * @brief Set the owner object.
   *
   * @param theOwner
   */
  const void SetOwner(const Handle_Naive_Object &theOwner) {
    myOwner = theOwner;
  }

  Naive_DEFINE_RTTI(Geometry, Naive_Object);

protected:
  /**
   * @brief Transform with a transformation.
   *
   * @param theTrsf Non-identy transformation.
   * @return Code.
   */
  Naive_EXPORT virtual Naive_Code transform(const math::Trsf3d &theTrsf) = 0;

protected:
  Handle_Naive_Object myOwner;
};

Naive_NAMESPACE_END(geometry);

using Naive_Geometry = ::naivecgl::geometry::Geometry;
Naive_DEFINE_HANDLE(Naive_Geometry);

#endif
