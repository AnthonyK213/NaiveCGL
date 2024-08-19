#include <naivecgl/BRepBuilderAPI/BuildSolidBlock.h>
#include <naivecgl/Common/Roster.h>
#include <naivecgl/Topology/Body.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Body_ask_edges(Naive_Body_t body, int *const n_edges,
                                  Naive_Edge_t **const edges) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_faces(Naive_Body_t body, int *const n_faces,
                                  Naive_Face_t **const faces) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_fins(Naive_Body_t body, int *const n_fins,
                                 Naive_Fin_t **const fins) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_location(Naive_Body_t body,
                                     Naive_Transform3d_t *const location) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_loops(Naive_Body_t body, int *const n_loops,
                                  Naive_Loop_t **const loops) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_orient(Naive_Body_t body,
                                   Naive_Orientation_t *const orientation) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_shells(Naive_Body_t body, int *const n_shells,
                                   Naive_Shell_t **const shells) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_vertices(Naive_Body_t body, int *const n_vertices,
                                     Naive_Vertex_t **const vertices) {
  return Naive_Code_not_implemented;
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

  ::naivecgl::brepbuilderapi::BuildSolidBlock aBuilder{*basis_set, x, y, z};
  Naive_CHECK_CODE(aBuilder.Status());
  Naive_ROSTER_ADD(aBuilder.Body(), *body);

  return Naive_Code_ok;
}
