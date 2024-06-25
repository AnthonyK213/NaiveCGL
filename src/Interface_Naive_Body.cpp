#include <naivecgl/Topology/Body.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Body_ask_location(const Naive_Body_t body,
                                     Naive_Transform3d_t *const location) {
  return Naive_Code_not_implemented;
}

Naive_Code_t
Naive_Body_ask_orientation(const Naive_Body_t body,
                           Naive_Orientation_t *const orientation) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_edges(const Naive_Body_t body, int *const n_edges,
                                  Naive_Edge_t *const edges) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_faces(const Naive_Body_t body, int *const n_faces,
                                  Naive_Face_t *const faces) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_fins(const Naive_Body_t body, int *const n_fins,
                                 Naive_Fin_t *const fins) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_loops(const Naive_Body_t body, int *const n_loops,
                                  Naive_Loop_t *const loops) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_shells(const Naive_Body_t body, int *const n_shells,
                                   Naive_Shell_t *const shells) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_vertices(const Naive_Body_t body,
                                     int *const n_vertices,
                                     Naive_Vertex_t *const vertices) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_boolean(const Naive_Body_t target, const int n_tools,
                                const Naive_Body_t *tools,
                                const Naive_Body_boolean_o_t *options) {
  return Naive_Code_not_implemented;
}
