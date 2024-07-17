#include <naivecgl/Common/Roster.h>
#include <naivecgl/Common/TObject.h>

Naive_NAMESPACE_BEGIN(common);

TObject::TObject() : myObj() {}

TObject::TObject(const Handle_Naive_Object &theObj) : myObj(theObj) {
  if (myObj)
    myObj->myTag_ = Naive_Roster::Resolve().NewTag();
}

Naive_Integer TObject::GetRefCount() const noexcept {
  return myObj ? myObj->GetRefCount() : 0;
}

Naive_NAMESPACE_END(common);
