#ifndef _NaiveCGL_BRepBOAPI_BO_HeaderFile
#define _NaiveCGL_BRepBOAPI_BO_HeaderFile

#include "../Common/Command.h"

Naive_NAMESPACE_BEGIN(brep_bo_api);

class BO : public common::Command {
public:
  Naive_EXPORT Naive_Real Fuzzy() const { return myFuzzy; }

  Naive_EXPORT void SetFuzzy();

protected:
  Naive_Real myFuzzy;
};

Naive_NAMESPACE_END(brep_bo_api);

#endif
