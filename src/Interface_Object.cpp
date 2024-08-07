#include <naivecgl/Common/Roster.h>
#include <naivecgl/Common/TClassType.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Object_ask_class(Naive_Object_t object,
                                    Naive_Class_t *const class_) {
  if (!class_)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Object, object, H);
  *class_ = Naive_TClassType::GetClass(H->GetClassType());

  return Naive_Code_ok;
}

Naive_Code_t Naive_Object_delete(Naive_Object_t object) {
  return Naive_Roster::Resolve().Erase(object);
}
