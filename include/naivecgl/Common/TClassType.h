#ifndef _NaiveCGL_Common_TClassType_HeaderFile
#define _NaiveCGL_Common_TClassType_HeaderFile

#include "ClassType.h"

#include <unordered_map>

Naive_NAMESPACE_BEGIN(common);

class TClassType final {
public:
  Naive_EXPORT TClassType();

  Naive_EXPORT TClassType(const Naive_Class theClass,
                          const Handle_Naive_ClassType &theClassType);

  Naive_EXPORT Naive_Class GetClass() const;

  const Handle_Naive_ClassType &GetClassType() const { return myClassType; }

  Naive_Bool IsNull() const { return myClassType.IsNull(); }

  Naive_EXPORT Naive_CStr Name() const;

  Naive_EXPORT Naive_Size Size() const;

  Naive_EXPORT Naive_Class Super() const;

  Naive_EXPORT Naive_Bool IsSubClass(const Naive_Class theClass) const;

  Naive_EXPORT static Naive_Class
  GetClass(const Handle_Naive_ClassType &theClassType);

  Naive_EXPORT static TClassType Resolve(const Naive_Class theClass);

private:
  using Registry = ::std::unordered_map<Naive_Class, TClassType>;

  static const Registry &getRegistry();

private:
  Handle_Naive_ClassType myClassType;
};

Naive_NAMESPACE_END(common);

using Naive_TClassType = ::naivecgl::common::TClassType;

#endif
