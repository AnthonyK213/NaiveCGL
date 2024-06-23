#ifndef _NaiveCGL_BndShape_ConvexHull3D_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull3D_HeaderFile

#include "../Common/Handle.h"
#include "../Geometry/HalfEdgeMesh.h"
#include "../Geometry/TriangleSoup.h"
#include "../Math/Pnt3d.h"

Naive_NAMESPACE_BEGIN(bndshape);

/// @brief Calculates the convex hull of a set of 3d points.
class ConvexHull3D final : public Naive_Transient {
public:
  Naive_EXPORT
  ConvexHull3D(const Naive_Pnt3dList1 &thePoints,
               Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull);

  Naive_EXPORT
  ConvexHull3D(Naive_Pnt3dList1 &&thePoints,
               Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull) noexcept;

  Naive_EXPORT ConvexHull3D(const ConvexHull3D &theOther) = delete;

  Naive_EXPORT ConvexHull3D(ConvexHull3D &&theOther) = delete;

  Naive_EXPORT void SetAlgorithm(Naive_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Pnt3d &thePoint,
                        const Naive_Bool thePerform = Naive_False);

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Handle_Naive_Poly ConvexHull() const;

public:
  class Impl {
  public:
    virtual ~Impl();

    virtual void Perform() = 0;

    virtual void Add(const Naive_Pnt3d &thePoint,
                     const Naive_Bool thePerform) = 0;

    Naive_Code Status() const { return myStatus; }

    virtual Handle_Naive_Poly ConvexHull() const;

  protected:
    explicit Impl(Naive_Pnt3dList1 &thePoints);

  protected:
    Naive_Pnt3dList1 *myPoints;
    Handle_Naive_Mesh myConvexHull;
    mutable Naive_Code myStatus;
  };

private:
  Naive_Pnt3dList1 myPoints;
  ::std::unique_ptr<Impl> myImpl;
  Naive_Algorithm myAlgo;
};

Naive_NAMESPACE_END(bndshape);

#endif
