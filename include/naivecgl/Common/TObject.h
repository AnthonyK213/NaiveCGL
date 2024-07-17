#ifndef _NaiveCGL_Common_TObject_HeaderFile
#define _NaiveCGL_Common_TObject_HeaderFile

#include "Handle.h"

Naive_NAMESPACE_BEGIN(common);

class TObject final {
public:
  Naive_EXPORT TObject();

  Naive_EXPORT TObject(const Handle_Naive_Object &theObj);

  Naive_EXPORT Naive_Integer GetRefCount() const noexcept;

  Naive_Tag Tag() const { return myObj ? myObj->myTag_ : 0; }

  const Handle_Naive_Object &GetObject() const { return myObj; }

  Naive_Bool IsNull() const { return myObj.IsNull(); }

private:
  Handle_Naive_Object myObj;
};

Naive_NAMESPACE_END(common);

using Naive_TObject = ::naivecgl::common::TObject;

#endif
