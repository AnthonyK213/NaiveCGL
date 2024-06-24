#include <naivecgl/Common/Object.h>

Naive_NAMESPACE_BEGIN(common);

Object::Object() : myRefCount_(0) {}

Object::Object(const Object &) : myRefCount_(0) {}

Object &Object::operator=(const Object &) { return *this; }

Object::~Object() {}

Object *Object::This() const {
  if (GetRefCount() == 0)
    throw ::std::runtime_error("Attempt to create handle to object created in "
                               "stack, not yet constructed, or destroyed");
  return const_cast<Object *>(this);
}

Naive_NAMESPACE_END(common);
