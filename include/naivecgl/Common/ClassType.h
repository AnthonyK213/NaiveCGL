#ifndef _NaiveCGL_Common_Class_HeaderFile
#define _NaiveCGL_Common_Class_HeaderFile

#include "../Collection/Hash.h"
#include "../Common/String.h"
#include "Handle.h"

#include <typeindex>
#include <typeinfo>

#define Naive_DEFINE_RTTI(Class_, Base_)                                       \
public:                                                                        \
  using base_type = Base_;                                                     \
  Naive_EXPORT static ::naivecgl::common::handle<                              \
      ::naivecgl::common::ClassType>                                           \
  get_class_type();                                                            \
  Naive_EXPORT virtual ::naivecgl::common::handle<                             \
      ::naivecgl::common::ClassType>                                           \
  GetClassType() const Naive_OVERRIDE;

#define Naive_IMPLEMENT_RTTI(Class_)                                           \
  Handle_Naive_ClassType Class_::get_class_type() {                            \
    return Naive_ClassType::Resolve<Class_>();                                 \
  }                                                                            \
  Handle_Naive_ClassType Class_::GetClassType() const {                        \
    return Class_::get_class_type();                                           \
  }

#define Naive_CLASS(Class_) Class_::get_class_type()

Naive_NAMESPACE_BEGIN(common);

class TClassType;

class ClassType final : public Naive_Object {
  friend class TClassType;

public:
  Naive_CStr Name() const { return myIndex.name(); }

  Naive_Size Size() const { return mySize; }

  const Naive_Handle<ClassType> &Super() const { return mySuper; };

  Naive_EXPORT Naive_Bool
  IsSubClass(const Naive_Handle<ClassType> &theClass) const;

  Naive_EXPORT ~ClassType();

  Naive_EXPORT static Naive_Handle<ClassType>
  Register(const ::std::type_info &theInfo, const Naive_Size theSize,
           const Naive_Handle<ClassType> &theSuper);

  Naive_DEFINE_RTTI(ClassType, Naive_Object);

public:
  template <class T> static Naive_Handle<ClassType> Resolve();

private:
  using Registry = Naive_Hash<::std::type_index, Naive_Handle<ClassType>>;

  ClassType(const ::std::type_info &theInfo, const Naive_Size theSize,
            const Naive_Handle<ClassType> &theSuper);

  static Registry &getRegistry();

private:
  Naive_Handle<ClassType> mySuper;
  ::std::type_index myIndex;
  Naive_Size mySize;
};

template <class T> Naive_Handle<ClassType> ClassType::Resolve() {
  return ClassType::Register(typeid(T), sizeof(T),
                             ClassType::Resolve<typename T::base_type>());
}

template <> inline Naive_Handle<ClassType> ClassType::Resolve<void>() {
  return nullptr;
}

Naive_NAMESPACE_END(common);

using Naive_ClassType = ::naivecgl::common::ClassType;
Naive_DEFINE_HANDLE(Naive_ClassType);

#endif
