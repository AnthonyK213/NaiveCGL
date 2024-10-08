#ifndef _NaiveCGL_Topology_Shell_HeaderFile
#define _NaiveCGL_Topology_Shell_HeaderFile

#include "../Collection/LinkedList.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;
class Region;
class Face;
class Edge;
class Vertex;

class Shell final : public Naive_Topol {
  friend class Body;
  friend class euler_op::MakeBodyFaceVertex;
  friend class euler_op::MakeFaceEdge;

public:
  Naive_EXPORT Shell();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Region *ParentRegion() const;

  Naive_EXPORT const Naive_Handle<Vertex> GetVertex() const { return myVertex; }

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_EXPORT Naive_Code SetVertex(const Naive_Handle<Vertex> &theVert);

  Naive_EXPORT Naive_Code AppendFace(const Naive_Handle<Face> &theFace);

  Naive_EXPORT Naive_LinkedList<Naive_Handle<Face>> GetFaces() const;

  Naive_DEFINE_RTTI(Shell, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Region *myRegion;              /* Parent region. */
  Naive_Handle<Face> myFace;     /* Head of faces in the shell. */
  Naive_Handle<Edge> myEdge;     /* Head of wireframe edges in the body. */
  Naive_Handle<Vertex> myVertex; /* If shell consists of a single vertex, this
                                    is it; else null. */
};

Naive_NAMESPACE_END(topology);

using Naive_Shell = ::naivecgl::topology::Shell;
Naive_DEFINE_HANDLE(Naive_Shell);

#endif
