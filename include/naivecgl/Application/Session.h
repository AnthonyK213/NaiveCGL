#ifndef _NaiveCGL_Application_Session_HeaderFile
#define _NaiveCGL_Application_Session_HeaderFile

#include "../Common/Handle.h"

Naive_NAMESPACE_BEGIN(application);

class Session : public Naive_Object {
public:
private:
};

Naive_NAMESPACE_END(application);

using Naive_Session = ::naivecgl::application::Session;
Naive_DEFINE_HANDLE(Naive_Session);

#endif
