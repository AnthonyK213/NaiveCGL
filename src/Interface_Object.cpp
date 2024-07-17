#include <naivecgl/Common/Roster.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Object_ask_class(Naive_Object_t object,
                                    Naive_Class_t *const class_) {
  if (!class_)
    return Naive_Code_null_arg_address;

  Naive_TObject anTObj;
  Naive_Code aCode = Naive_Roster::Resolve().Find(object, anTObj);
  if (aCode != Naive_Code_ok)
    return aCode;

  Naive_Handle<Naive_Object> H = anTObj.GetObject();
  *class_ = H ? H->get_class() : Naive_Class_null;

  return Naive_Code_ok;
}

Naive_Code_t Naive_Object_delete(Naive_Object_t object) {
  return Naive_Roster::Resolve().Erase(object);
}
