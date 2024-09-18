#ifndef _NaiveCGL_BRepBuilderAPI_Builder_HeaderFile
#define _NaiveCGL_BRepBuilderAPI_Builder_HeaderFile

#include "../Common/Command.h"
#include "../Common/Handle.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;

Naive_NAMESPACE_END(topology);

Naive_NAMESPACE_BEGIN(brep_builder_api);

class Builder : public common::Command {
public:
  Naive_EXPORT virtual void Build() = 0;

  Naive_EXPORT virtual Naive_Handle<topology::Body> Body() const;

protected:
  Naive_EXPORT Builder();

protected:
  Naive_Handle<topology::Body> myBody;
};

Naive_NAMESPACE_END(brep_builder_api);

#endif
