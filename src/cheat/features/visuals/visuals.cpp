#include "visuals.hpp"
#include "../config.hpp"

#include "link.hpp"

#include <format>

void c_esp::run() {
  if(!settings::esp::esp_enabled)
    return;

  for(auto entidx = 1; entidx <= g_tf2.entity_list->get_highest_ent_index(); ++entidx) {
    if(auto ent = g_tf2.entity_list->get_client_entity(entidx)) {
      if(ent->is_dormant()) // entity is dormant, skip over it
        continue;

      auto entity = ent->as<c_entity>();

      // entity is invalid or is dead, skip
      if(!entity || entity->is_dead())
        continue;

      // entity is the localplayer, skip
      if(entity == ctx->local_player)
        continue;

      int x{}, y{}, w{}, h{};

      // FIXME: Riley; There is currently an issue where all "Player" texts only originate
      // at 0, 0, 0. My assumption as it is right now may be due to clientclasses or one of the
      // IClient virtual method tables being out of date. As stepping through the get_bounds()
      // function with a debugger results in us never hitting CTFPlayer as our class.
      // If anyone can figure it out, please make a PR!
      if(!get_bounds(entity, x, y, w, h)) {

        const int draw_x = x + (w / 2);
        int draw_y = y + (h / 2);
        g_draw_threaded.string(nullptr, draw_x, draw_y, true, e_text_align::TEXT_LEFT,
                               ImColor(1.f, 1.f, 1.f, 1.f), "Player");
      }
    }
  }
}

// credits: spook953?
// nearly every esp is the same so
bool c_esp::get_bounds(c_entity* entity, int& x, int& y, int& w, int& h) {
  vec3  vec_mins{}, vec_maxs{};

  // get our world transform
  auto& trans = const_cast<matrix3x4&>(entity->renderable_to_world_transform());

  bool  is_player = false;

  switch(entity->get_class_id()) {
    case e_class_ids::CTFPlayer: {
      is_player = true;
      vec_mins = entity->mins();
      vec_maxs = entity->maxs();

      if(entity->entidx() == g_tf2.engine_client->get_local_player()) {
        // QAngle va; g_tf2.engine_client->get_view_angles(va);
        // va.x = va.y = 0.f;
        //  TODO: implement this
        //  we need to add anglematrix and matrixsetcolumn to the mathex namespace
      }

      break;
    }
    case e_class_ids::CObjectSentrygun:
    case e_class_ids::CObjectDispenser:
    case e_class_ids::CObjectTeleporter: {
      vec_mins = entity->mins();
      vec_maxs = entity->maxs();
      break;
    }
    default: {
      entity->get_render_bounds(vec_mins, vec_maxs);
      break;
    }
  }

  // generate our points
  vec3 points[] = {
      vec3(vec_mins.x, vec_mins.y, vec_mins.z), vec3(vec_mins.x, vec_maxs.y, vec_mins.z),
      vec3(vec_maxs.x, vec_maxs.y, vec_mins.z), vec3(vec_maxs.x, vec_mins.y, vec_mins.z),
      vec3(vec_maxs.x, vec_maxs.y, vec_maxs.z), vec3(vec_mins.x, vec_maxs.y, vec_maxs.z),
      vec3(vec_mins.x, vec_mins.y, vec_maxs.z), vec3(vec_maxs.x, vec_mins.y, vec_maxs.z)};

  // create a transform array
  vec3 transformed[8] = {};

  // iterate and transform
  for(int n = 0; n < 8; ++n) {
    mathex::vector_transform(points[n], trans, transformed[n]);
  }

  vec3 flb{}, brt{}, blb{}, frt{}, frb{}, brb{}, blt{}, flt{};

  if(g_tf2.w2s(transformed[3], flb) && g_tf2.w2s(transformed[5], brt) &&
     g_tf2.w2s(transformed[0], blb) && g_tf2.w2s(transformed[4], frt) &&
     g_tf2.w2s(transformed[2], frb) && g_tf2.w2s(transformed[1], brb) &&
     g_tf2.w2s(transformed[6], blt) && g_tf2.w2s(transformed[7], flt) &&
     g_tf2.w2s(transformed[6], blt) && g_tf2.w2s(transformed[7], flt)) {
    vec3  array[] = {flb, brt, blb, frt, frb, brb, flt, flt};

    float left = flb.x;
    float top = flb.y;
    float right = flb.x;
    float bottom = flb.y;

    for(int n = 1; n < 8; ++n) {
      // we should probably clean this up
      if(left > array[n].x)
        left = array[n].x;

      if(top < array[n].y)
        top = array[n].y;

      if(right < array[n].x)
        right = array[n].x;

      if(bottom > array[n].y)
        bottom = array[n].y;

      float f_x = left;
      float f_y = bottom;
      float f_w = right - left;
      float f_h = top - bottom;

      if(is_player) {
        f_x += ((right - left) / 8.f);
        f_w -= (((right - left) / 8.f) * 2.f);
      }

      // C-Style casts here are explicit
      x = (int)f_x;
      y = (int)f_y;
      w = (int)f_w;
      h = (int)f_h;

      return x <= ctx->screen_width && (x + w) >= 0 && y <= ctx->screen_height && (y + h) >= 0;
    }
  }
  return false;
}
