#ifndef _NaiveCGL_BndShape_ConvexHull3D_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull3D_HeaderFile

#include <naivecgl/Common/Handle.h>
#include <naivecgl/Geometry/HalfEdgeMesh.h>
#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/TriangleSoup.h>

Naive_NAMESPACE_BEGIN(bndshape);

/// @brief Calculates the convex hull of a set of 3d points.
class ConvexHull3D final : public Naive_Transient {
public:
  Naive_EXPORT
  ConvexHull3D(const Naive_Point3dList &thePoints,
               Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull);

  Naive_EXPORT
  ConvexHull3D(Naive_Point3dList &&thePoints,
               Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull) noexcept;

  Naive_EXPORT ConvexHull3D(const ConvexHull3D &theOther) = delete;

  Naive_EXPORT ConvexHull3D(ConvexHull3D &&theOther) = delete;

  Naive_EXPORT void SetAlgorithm(Naive_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Point3d &thePoint,
                        const Naive_Bool thePerform = Naive_False);

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Handle_Naive_Poly ConvexHull() const;

public:
  class Impl {
  public:
    virtual ~Impl();

    virtual void Perform() = 0;

    virtual void Add(const Naive_Point3d &thePoint,
                     const Naive_Bool thePerform) = 0;

    Naive_Code Status() const { return myStatus; }

    virtual Handle_Naive_Poly ConvexHull() const;

  protected:
    explicit Impl(Naive_Point3dList &thePoints);

  protected:
    Naive_Point3dList *myPoints;
    Handle_Naive_Mesh myConvexHull;
    mutable Naive_Code myStatus;
  };

private:
  Naive_Point3dList myPoints;
  ::std::unique_ptr<Impl> myImpl;
  Naive_Algorithm myAlgo;
};

Naive_NAMESPACE_END(bndshape);

#endif
