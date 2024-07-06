#include <naivecgl/Common/TObject.h>

Naive_NAMESPACE_BEGIN(common);

TObject::TObject() : Object(), myTag_(Naive_Roster::Resolve().NewTag()) {}

TObject::TObject(const TObject &)
    : Object(), myTag_(Naive_Roster::Resolve().NewTag()) {}

TObject &TObject::operator=(const TObject &) { return *this; }

Naive_NAMESPACE_END(common);
