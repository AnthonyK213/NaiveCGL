#include <naivecgl/Common/TObject.h>

Naive_NAMESPACE_BEGIN(common);

TObject::TObject() : myTag_(0), myObj_() {}

TObject::TObject(const Handle_Naive_Object &theObj)
    : myTag_(Naive_Roster::Resolve().NewTag()), myObj_(theObj) {}

Naive_Integer TObject::GetRefCount() const noexcept {
  return myObj_ ? myObj_->GetRefCount() : 0;
}

Naive_NAMESPACE_END(common);
