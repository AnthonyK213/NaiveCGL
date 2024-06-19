#ifndef _NaiveCGL_Topology_Body_HeaderFile
#define _NaiveCGL_Topology_Body_HeaderFile

#include "Location.h"
#include "TBody.h"

Naive_NAMESPACE_BEGIN(topology);

class Body {
public:
  Naive_EXPORT Body();

  template <typename T, typename ::std::enable_if<
                            ::std::is_base_of<Body, T>::value>::type * = 0>
  Body(T &&theOther)
      : myTBody(::std::forward<T>(theOther).myTBody),
        myLocation(::std::forward<T>(theOther).myLocation),
        myOrient(::std::forward<T>(theOther).myOrientation) {}

  template <typename T>
  typename ::std::enable_if<::std::is_base_of<Body, T>::value>::type &
  operator=(T &&theOther) {
    myTBody = ::std::forward<T>(theOther).myTBody;
    myLocation = ::std::forward<T>(theOther).myLocation;
    myOrient = ::std::forward<T>(theOther).myOrientation;
    return *this;
  }

  Naive_EXPORT Naive_Bool IsNull() const { return myTBody.IsNull(); }

  Naive_EXPORT void Nullify() {
    myTBody.Nullify();
    myLocation.Clear();
    myOrient = Naive_Orientation_external;
  }

  Naive_EXPORT const Naive_Location &Location() const { return myLocation; }

  Naive_EXPORT Naive_Orientation Orientation() const { return myOrient; }

  Naive_EXPORT void SetOrientation(const Naive_Orientation theOrient) {
    myOrient = theOrient;
  }

  Naive_EXPORT const Handle_Naive_TBody &TBody() const { return myTBody; }

  Naive_EXPORT Naive_Class Class() const { return myTBody->Class(); }

  Naive_EXPORT Naive_Bool IsSame(const Body &theOther) const {
    return myTBody == theOther.myTBody && myLocation == theOther.myLocation;
  }

  Naive_EXPORT Naive_Bool IsEqual(const Body &theOther) const {
    return IsSame(theOther) && myOrient == theOther.myOrient;
  }

  Naive_EXPORT Naive_Bool operator==(const Body &theOther) const {
    return IsEqual(theOther);
  }

  Naive_EXPORT Naive_Bool IsNotEqual(const Body &theOther) const {
    return !IsEqual(theOther);
  }

  Naive_EXPORT Naive_Bool operator!=(const Body &theOther) const {
    return IsNotEqual(theOther);
  }

private:
  Handle_Naive_TBody myTBody;
  Naive_Location myLocation;
  Naive_Orientation myOrient;
};

Naive_NAMESPACE_END(topology);

using Naive_Body = ::naivecgl::topology::Body;

namespace std {

template <> struct hash<Naive_Body> {
  size_t operator()(const Naive_Body &theBody) const {
    // TODO: Hashing.
    return 0;
  }
};

} // namespace std

#endif
