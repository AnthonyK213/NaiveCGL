#include <naivecgl/Common/Roster.h>
#include <naivecgl/Common/TObject.h>

#include <naivecgl/Interface/NaiveCGL_c_macros.h>

Naive_NAMESPACE_BEGIN(common);

TObject::TObject()
    : myObj(nullptr), myStrong(Naive_False), myDeleted(Naive_False) {}

TObject::TObject(const Handle_Naive_Object &theObj, Naive_Bool theStrong)
    : myObj(theObj.get()), myStrong(theStrong), myDeleted(Naive_False) {
  if (myObj) {
    if (myObj->myTag_ == Naive_Object_null) {
      myObj->myTag_ = Naive_Roster::Resolve().NewTag();

      /* If tag is not null, then the object has already been added to the
       * roster, so do not increase the rc. */
      if (myStrong)
        myObj->IncrementRefCounter();
    }
  }
}

Naive_Integer TObject::GetRefCount() const noexcept {
  return myObj ? myObj->GetRefCount() : 0;
}

Handle_Naive_Object TObject::GetObject() const { return myObj; }

Naive_Bool TObject::IsNull() const { return myObj == nullptr; }

Naive_Bool TObject::IsStrong() const { return myStrong; }

Naive_Bool TObject::IsDeleted() const { return myDeleted; }

Naive_Tag TObject::Tag() const {
  return myDeleted ? Naive_Object_null : Tag(myObj);
}

Naive_Tag TObject::Tag(const Naive_Object *theObj) {
  return theObj ? theObj->myTag_ : Naive_Object_null;
}

void TObject::Delete() {
  if (IsDeleted())
    return;

  if (myObj && IsStrong())
    myObj->DecrementRefCounter();

  myObj = nullptr;
  myDeleted = Naive_True;
}

Naive_NAMESPACE_END(common);
