#include "render_view.hpp"

#include "link.hpp"

void iv_render_view::get_matrices_for_view(const c_view_setup& view, v_matrix* world_to_view,
                                           v_matrix* view_to_projection,
                                           v_matrix* world_to_projection,
                                           v_matrix* world_to_pixels) {
  memory::find_vfunc<void(__thiscall*)(void*, const c_view_setup&, v_matrix*, v_matrix*, v_matrix*,
                                       v_matrix*)>(this, 50u)(
      this, view, world_to_view, view_to_projection, world_to_projection, world_to_pixels);
}