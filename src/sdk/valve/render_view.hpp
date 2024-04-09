#pragma once
#include "view_setup.hpp"

class iv_render_view {
public:
  void get_matrices_for_view(const c_view_setup& view, v_matrix* world_to_view,
                             v_matrix* view_to_projection, v_matrix* world_to_projection,
                             v_matrix* world_to_pixels);
};