#ifndef _NaiveCGL_Common_Object_HeaderFile
#define _NaiveCGL_Common_Object_HeaderFile

#include "Macro.h"
#include "Type.h"

#include <atomic>

Naive_NAMESPACE_BEGIN(common);

template <typename T> class handle;
class ClassType;

class Object {
public:
  Naive_EXPORT Object();

  Naive_EXPORT Object(const Object &);

  Naive_EXPORT Object &operator=(const Object &);

  Naive_EXPORT virtual ~Object();

  Naive_EXPORT Object *This() const;

  inline Naive_Integer GetRefCount() const noexcept { return myRefCount_; }

  inline void IncrementRefCounter() noexcept { ++myRefCount_; }

  inline Naive_Integer DecrementRefCounter() noexcept { return --myRefCount_; }

  Naive_EXPORT virtual void Delete() const { delete this; }

public:
  using base_type = void;

  static constexpr Naive_Class get_class() { return Naive_Class_object; }

  Naive_EXPORT static handle<ClassType> get_class_type();

  Naive_EXPORT virtual handle<ClassType> GetClassType() const;

protected:
  ::std::atomic<Naive_Integer> myRefCount_;
};

Naive_NAMESPACE_END(common);

using Naive_Object = ::naivecgl::common::Object;

#endif
