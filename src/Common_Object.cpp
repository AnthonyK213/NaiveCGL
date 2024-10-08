﻿#include <naivecgl/Common/ClassType.h>
#include <naivecgl/Common/Object.h>
#include <naivecgl/Interface/NaiveCGL_c_macros.h>

Naive_NAMESPACE_BEGIN(common);

Object::Object() : myRefCount_(0), myTag_(Naive_Object_null) {}

Object::Object(const Object &) : myRefCount_(0), myTag_(Naive_Object_null) {}

Object &Object::operator=(const Object &) { return *this; }

Object::~Object() {}

Object *Object::This() const {
  if (GetRefCount() == 0)
    return nullptr;
  return const_cast<Object *>(this);
}

Handle_Naive_ClassType Object::get_class_type() {
  return Naive_ClassType::Resolve<Object>();
}

Handle_Naive_ClassType Object::GetClassType() const {
  return Object::get_class_type();
}

Naive_NAMESPACE_END(common);
