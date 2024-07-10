#ifndef _NaiveCGL_BRepAPI_Command_HeaderFile
#define _NaiveCGL_BRepAPI_Command_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(brepapi);

class Command {
public:
  Naive_EXPORT virtual ~Command();

  Naive_EXPORT virtual Naive_Code Status() const;

protected:
  Naive_EXPORT Command();

  Naive_EXPORT void SetStatus(Naive_Code theStatus);

private:
  Naive_Code myStatus;
};

Naive_NAMESPACE_END(brepapi);

#endif
