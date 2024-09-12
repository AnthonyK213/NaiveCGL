#include <naivecgl/Common/Roster.h>
#include <naivecgl/Common/TObject.h>
#include <naivecgl/Interface/NaiveCGL_c_macros.h>

Naive_NAMESPACE_BEGIN(common);

TObject::TObject() : myObj() {}

TObject::TObject(const Handle_Naive_Object &theObj) : myObj(theObj) {
  if (myObj)
    myObj->myTag_ = Naive_Roster::Resolve().NewTag();
}

Naive_Integer TObject::GetRefCount() const noexcept {
  return myObj ? myObj->GetRefCount() : 0;
}

Naive_Bool TObject::IsNull() const { return myObj.IsNull(); }

Naive_Tag TObject::Tag() const { return Tag(myObj.get()); }

Naive_Tag TObject::Tag(const Naive_Object *theObj) {
  return theObj ? theObj->myTag_ : Naive_Object_null;
}

Naive_NAMESPACE_END(common);
