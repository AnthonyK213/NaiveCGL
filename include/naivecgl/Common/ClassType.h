#ifndef _NaiveCGL_Common_Class_HeaderFile
#define _NaiveCGL_Common_Class_HeaderFile

#include "../Collection/Hash.h"
#include "../Common/String.h"
#include "Handle.h"

#include <typeindex>
#include <typeinfo>

#define Naive_DEFINE_RTTI(Class_, Base_, Desc_)                                \
public:                                                                        \
  using base_type = Base_;                                                     \
  static constexpr Naive_Class get_class() { return Desc_; }                   \
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

Naive_NAMESPACE_BEGIN(common);

class ClassType final : public Naive_Object {
public:
  Naive_CStr Name() const { return myInfo.name(); }

  Naive_Class Class() const { return myClass; }

  Naive_Size Size() const { return mySize; }

  const Naive_Handle<ClassType> &Super() const { return mySuper; };

  Naive_EXPORT Naive_Bool
  IsSubClass(const Naive_Handle<ClassType> &theClass) const;

  Naive_EXPORT Naive_Bool IsSubClass(const Naive_Class theClass) const;

  Naive_EXPORT ~ClassType();

  Naive_EXPORT static Naive_Handle<ClassType>
  Register(const ::std::type_info &theInfo, const Naive_Class theClass,
           const Naive_Size theSize, const Naive_Handle<ClassType> &theSuper);

  Naive_DEFINE_RTTI(ClassType, Naive_Object, Naive_Class_class);

public:
  template <class T> static Naive_Handle<ClassType> Resolve();

private:
  using Registry = Naive_Hash<Naive_Class, Naive_Handle<ClassType>>;

  ClassType(const ::std::type_info &theInfo, const Naive_Class theClass,
            const Naive_Size theSize, const Naive_Handle<ClassType> &theSuper);

  static Registry &getRegistry();

private:
  Naive_Handle<ClassType> mySuper;
  ::std::type_index myInfo;
  Naive_Size mySize;
  Naive_Class myClass;
};

template <class T> Naive_Handle<ClassType> ClassType::Resolve() {
  return ClassType::Register(typeid(T), T::get_class(), sizeof(T),
                             ClassType::Resolve<typename T::base_type>());
}

template <> inline Naive_Handle<ClassType> ClassType::Resolve<void>() {
  return nullptr;
}

Naive_NAMESPACE_END(common);

using Naive_ClassType = ::naivecgl::common::ClassType;
Naive_DEFINE_HANDLE(Naive_ClassType);

#endif
