#ifndef _NaiveCGL_Geometry_Triangulation_HeaderFile
#define _NaiveCGL_Geometry_Triangulation_HeaderFile

#include "../Common/ClassType.h"
#include "../Math/Pnt3d.h"
#include "../Math/Vec3d.h"
#include "Geometry.h"
#include "Triangle.h"

Naive_NAMESPACE_BEGIN(geometry);

class Triangulation : public Naive_Geometry {
  using VertexList = Naive_List1<Naive_Pnt3d>;
  using TriangleList = Naive_List1<Naive_Triangle>;

public:
  Naive_EXPORT Triangulation();

  template <typename V, typename T,
            typename = Naive_WHERE__IS_REF_OF(V, VertexList),
            typename = Naive_WHERE__IS_REF_OF(T, TriangleList)>
  Triangulation(V &&theVertices, T &&theTriangles) {
    myVertices = ::std::forward<V>(theVertices);
    myTriangles = ::std::forward<T>(theTriangles);
  }

public:
  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT const VertexList &Vertices() const { return myVertices; }

  Naive_EXPORT const TriangleList &Triangles() const { return myTriangles; }

  Naive_DEFINE_RTTI(Triangulation, Naive_Object);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  VertexList myVertices;
  TriangleList myTriangles;
};

Naive_NAMESPACE_END(geometry);

using Naive_Triangulation = ::naivecgl::geometry::Triangulation;
Naive_DEFINE_HANDLE(Naive_Triangulation);

#endif
