#ifndef _NaiveCGL_Common_TObject_HeaderFile
#define _NaiveCGL_Common_TObject_HeaderFile

#include "Handle.h"
#include "Roster.h"

Naive_NAMESPACE_BEGIN(common);

class TObject : public Naive_Object {
public:
  Naive_EXPORT TObject();

  Naive_EXPORT TObject(const TObject &);

  Naive_EXPORT TObject &operator=(const TObject &);

  inline Naive_Tag Tag() const { return myTag_; }

private:
  Naive_Tag myTag_;
};

Naive_NAMESPACE_END(common);

using Naive_TObject = ::naivecgl::common::TObject;
Naive_DEFINE_HANDLE(Naive_TObject);

#endif
