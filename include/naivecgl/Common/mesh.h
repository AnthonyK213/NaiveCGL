#ifndef _NaiveCGL_Common_mesh_Header
#define _NaiveCGL_Common_mesh_Header

#include <naivecgl/Shape/HalfEdgeMesh.h>
#include <naivecgl/Shape/TriangleSoup.h>

using Naive_Poly3D = naivecgl::shape::TriangleSoup<Naive_Real, Naive_Integer>;
using Naive_Mesh3D = naivecgl::shape::TriangleSoup<Naive_Real, Naive_Integer>;

using Naive_H_Poly3D = Naive_H<Naive_Poly3D>;
using Naive_H_Mesh3D = Naive_H<Naive_Mesh3D>;

#endif
