#ifndef _NaiveCGL_BRepBuilderAPI_BuildSolidBlock_HeaderFile
#define _NaiveCGL_BRepBuilderAPI_BuildSolidBlock_HeaderFile

#include "../Math/Ax2.h"
#include "Builder.h"

Naive_NAMESPACE_BEGIN(brep_builder_api);

class BuildSolidBlock : public Builder {
public:
  Naive_EXPORT BuildSolidBlock();

  Naive_EXPORT BuildSolidBlock(const Naive_Ax2 &theAx2, const Naive_Real theX,
                               const Naive_Real theY, const Naive_Real theZ);

  Naive_EXPORT void Init(const Naive_Ax2 &theAx2, const Naive_Real theX,
                         const Naive_Real theY, const Naive_Real theZ);

  Naive_EXPORT virtual void Build() Naive_OVERRIDE;

private:
  Naive_Ax2 myAx2;
  Naive_Real myX;
  Naive_Real myY;
  Naive_Real myZ;
};

Naive_NAMESPACE_END(brep_builder_api);

#endif
