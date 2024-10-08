#include <naivecgl/BRepBuilderAPI/BuildSolidBlock.h>
#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Vertex.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Body_ask_edges(Naive_Body_t body, int *const n_edges,
                                  Naive_Edge_t **const edges) {
  if (!n_edges)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Body, body, H);
  Naive_LinkedList<Handle_Naive_Edge> anEdges = H->GetEdges();
  *n_edges = static_cast<int>(anEdges.size());

  if (edges) {
    Naive_unique_ptr<Naive_Edge_t> result;
    Naive_ALLOC_ARRAY(Naive_Edge_t, *n_edges, &result);
    int i = 0;
    for (const Handle_Naive_Edge &edge : anEdges) {
      Naive_ROSTER_ADD(edge, Naive_True, result.get()[i++]);
    }
    *edges = result.release();
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Body_ask_faces(Naive_Body_t body, int *const n_faces,
                                  Naive_Face_t **const faces) {
  if (!n_faces)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Body, body, H);
  Naive_LinkedList<Handle_Naive_Face> aFaces = H->GetFaces();
  *n_faces = static_cast<int>(aFaces.size());

  if (faces) {
    Naive_unique_ptr<Naive_Face_t> result;
    Naive_ALLOC_ARRAY(Naive_Face_t, *n_faces, &result);
    int i = 0;
    for (const Handle_Naive_Face &face : aFaces) {
      Naive_ROSTER_ADD(face, Naive_True, result.get()[i++]);
    }
    *faces = result.release();
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Body_ask_fins(Naive_Body_t body, int *const n_fins,
                                 Naive_Fin_t **const fins) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_loops(Naive_Body_t body, int *const n_loops,
                                  Naive_Loop_t **const loops) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_parent(Naive_Body_t body,
                                   Naive_Body_t *const parent) {
  if (!parent)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Body, body, H);
  Naive_Body *aParent = H->ParentBody();
  *parent = Naive_TObject::Tag(aParent);

  return Naive_Code_ok;
}

Naive_Code_t Naive_Body_ask_regions(Naive_Body_t body, int *const n_regions,
                                    Naive_Region_t **const regions) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_shells(Naive_Body_t body, int *const n_shells,
                                   Naive_Shell_t **const shells) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_vertices(Naive_Body_t body, int *const n_vertices,
                                     Naive_Vertex_t **const vertices) {
  if (!n_vertices)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Body, body, H);
  Naive_LinkedList<Handle_Naive_Vertex> aVerts = H->GetVertices();
  *n_vertices = static_cast<int>(aVerts.size());

  if (vertices) {
    Naive_unique_ptr<Naive_Vertex_t> result;
    Naive_ALLOC_ARRAY(Naive_Vertex_t, *n_vertices, &result);
    int i = 0;
    for (const Handle_Naive_Face &vertex : aVerts) {
      Naive_ROSTER_ADD(vertex, Naive_True, result.get()[i++]);
    }
    *vertices = result.release();
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Body_boolean(Naive_Body_t target, int n_tools,
                                const Naive_Body_t *tools,
                                const Naive_Body_boolean_o_t *options) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_create_solid_block(double x, double y, double z,
                                           const Naive_Ax2_sf_t *basis_set,
                                           Naive_Body_t *const body) {
  if (!basis_set || !body)
    return Naive_Code_null_arg_address;

  ::naivecgl::brep_builder_api::BuildSolidBlock aBuilder{*basis_set, x, y, z};
  Naive_CHECK_CODE(aBuilder.Status());
  Naive_ROSTER_ADD(aBuilder.Body(), Naive_True, *body);

  return Naive_Code_ok;
}
