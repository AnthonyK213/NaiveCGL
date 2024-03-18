#include <naivecgl/Geometry/Circle.h>

Naive_NAMESPACE_BEGIN(geometry);

Circle::Circle() {}

Circle::Circle(const Plane &thePlane, const Naive_Real theRadius)
    : myPlane(thePlane), myRadius(theRadius) {}

Circle::Circle(const Naive_Circle_T &theCircle)
    : myPlane(theCircle.plane), myRadius(theCircle.radius) {}

Naive_NAMESPACE_END(geometry);
