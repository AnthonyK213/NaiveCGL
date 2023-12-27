#ifndef _NaiveCGL_Geometry_geometry_HeaderFile
#define _NaiveCGL_Geometry_geometry_HeaderFile

#include <naivecgl/Geometry/Circle.h>
#include <naivecgl/Geometry/Interval.h>
#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Geometry/Rectangle.h>

#include <naivecgl/Geometry/HalfEdgeMesh.h>
#include <naivecgl/Geometry/TriangleSoup.h>

using Naive_Circle = naivecgl::geometry::Circle;
using Naive_Interval = naivecgl::geometry::Interval;
using Naive_Line = naivecgl::geometry::Line;
using Naive_Plane = naivecgl::geometry::Plane;
using Naive_Rectangle = naivecgl::geometry::Rectangle;

using Naive_Mesh = naivecgl::geometry::HalfEdgeMesh;
using Naive_Poly = naivecgl::geometry::TriangleSoup;
using Naive_H_Mesh = Naive_H<Naive_Mesh>;
using Naive_H_Poly = Naive_H<Naive_Poly>;

#endif
