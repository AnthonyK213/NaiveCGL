#ifndef _NaiveCGL_Common_Command_HeaderFile
#define _NaiveCGL_Common_Command_HeaderFile

#include "Macro.h"
#include "Type.h"

Naive_NAMESPACE_BEGIN(common);

class Command {
public:
  Naive_EXPORT virtual ~Command();

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Naive_Bool IsDone() const;

  Naive_EXPORT void Reset();

protected:
  Naive_EXPORT Command();

  Naive_EXPORT void SetStatus(Naive_Code theStatus);

  Naive_EXPORT void ResetStatus();

  Naive_EXPORT void Done();

  Naive_EXPORT virtual void ResetInternal();

private:
  Naive_Code myStatus;
};

Naive_NAMESPACE_END(common);

#endif
