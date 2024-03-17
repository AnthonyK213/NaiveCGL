#ifndef _NaiveCGL_BndShape_ConvexHull3D_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull3D_HeaderFile

#include <naivecgl/Geometry/HalfEdgeMesh.h>
#include <naivecgl/Geometry/TriangleSoup.h>

Naive_NAMESPACE_BEGIN(bndshape);

/// @brief Calculates the convex hull of a set of 3d points.
class ConvexHull3D {
public:
  Naive_EXPORT ConvexHull3D(
      const Naive_Point3dList &thePoints,
      Naive_ConvexHull3D_Algorithm theAlgo = Naive_ConvexHull3D_Quickhull);

  Naive_EXPORT ConvexHull3D(Naive_Point3dList &&thePoints,
                            Naive_ConvexHull3D_Algorithm theAlgo =
                                Naive_ConvexHull3D_Quickhull) noexcept;

  Naive_EXPORT ConvexHull3D(const ConvexHull3D &theOther) = delete;

  Naive_EXPORT ConvexHull3D(ConvexHull3D &&theOther) = delete;

  Naive_EXPORT ~ConvexHull3D();

  Naive_EXPORT void SetAlgorithm(Naive_ConvexHull3D_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Point3d &thePoint,
                        const Naive_Bool thePerform = false);

  Naive_EXPORT Naive_ConvexHull3D_Status Status() const;

  Naive_EXPORT Naive_H_Poly ConvexHull() const;

public:
  class Naive_EXPORT Impl {
  public:
    virtual ~Impl();

    virtual void Perform() = 0;

    virtual void Add(const Naive_Point3d &thePoint,
                     const Naive_Bool thePerform) = 0;

    Naive_ConvexHull3D_Status Status() const { return myStatus; }

    virtual Naive_H_Poly ConvexHull() const;

  protected:
    explicit Impl(Naive_Point3dList &thePoints);

  protected:
    Naive_Point3dList *myPoints;
    Naive_H_Mesh myConvexHull;
    Naive_ConvexHull3D_Status myStatus;
  };

private:
  Naive_Point3dList myPoints;
  std::unique_ptr<Impl> myImpl;
  Naive_ConvexHull3D_Algorithm myAlgo;
};

Naive_NAMESPACE_END(bndshape);

#endif
