#ifndef _NaiveCGL_EulerOp_Operator_HeaderFile
#define _NaiveCGL_EulerOp_Operator_HeaderFile

#include "../Collection/List1.h"
#include "../Common/Command.h"
#include "../Common/Handle.h"

Naive_NAMESPACE_BEGIN(topology);

class Topol;
class Body;
class Region;
class Shell;
class Face;
class Loop;
class Fin;
class Edge;
class Vertex;

Naive_NAMESPACE_END(topology);

Naive_NAMESPACE_BEGIN(eulerop);

class TEV;

class Operator : public common::Command {
public:
  Naive_EXPORT virtual void Perform();

  Naive_EXPORT virtual const TEV &GetTEV() const = 0;

  const Naive_List1<Naive_Handle<topology::Topol>> &NewTopols() {
    return myNew;
  }

  const Naive_List1<Naive_Handle<topology::Topol>> &DelTopols() {
    return myDel;
  }

protected:
  Naive_EXPORT Operator() : common::Command(), myNew(), myDel() {}

  Naive_EXPORT virtual Naive_Code CheckParams() const;

  Naive_EXPORT virtual Naive_Code PerformInternal() = 0;

protected:
  Naive_List1<Naive_Handle<topology::Topol>> myNew;
  Naive_List1<Naive_Handle<topology::Topol>> myDel;
};

#define Naive_DEFINE_EO(Op_)                                                   \
public:                                                                        \
  Naive_EXPORT static const TEV &get_TEV();                                    \
  Naive_EXPORT virtual const TEV &GetTEV() const Naive_OVERRIDE;

#define Naive_IMPLEMENT_EO(Op_, ...)                                           \
  const TEV &Op_::GetTEV() const { return Op_::get_TEV(); }                    \
  const TEV &Op_::get_TEV() {                                                  \
    static TEV aTEV{__VA_ARGS__};                                              \
    return aTEV;                                                               \
  }

Naive_NAMESPACE_END(eulerop);

#endif
