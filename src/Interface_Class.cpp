#include <naivecgl/Common/EnumCaster.h>
#include <naivecgl/Common/TClassType.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Class_ask_superclass(Naive_Class_t class_,
                                        Naive_Class_t *const superclass) {
  if (!superclass)
    return Naive_Code_null_arg_address;

  Naive_ENUM_CAST(Naive_Class, class_, class_enum);
  auto t = Naive_TClassType::Resolve(class_enum);
  *superclass = t.Super();

  return Naive_Code_ok;
}

Naive_Code_t Naive_Class_is_subclass(Naive_Class_t may_be_subclass,
                                     Naive_Class_t class_,
                                     Naive_Logical_t *const is_subclass) {
  if (!is_subclass)
    return Naive_Code_null_arg_address;

  Naive_ENUM_CAST(Naive_Class, may_be_subclass, may_be_subclass_enum);
  Naive_ENUM_CAST(Naive_Class, class_, class_enum);
  auto t = Naive_TClassType::Resolve(may_be_subclass_enum);
  *is_subclass = t.IsSubClass(class_enum);

  return Naive_Code_ok;
}
