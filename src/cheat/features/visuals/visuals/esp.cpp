#include "../visuals.hpp"

#include "../../config.hpp"

void c_esp::run() {
  if(!ctx->local_player || !g_tf2.engine_vgui->is_game_ui_visible())
    return;

  // clear all entities we have in our vector
  entities.clear();

  // iterate through the entity list
  for(int entidx = 1; entidx <= g_tf2.entity_list->get_highest_ent_index(); ++entidx) {
    // entity is a player
    if(auto ent = g_tf2.entity_list->get_client_entity(entidx)->as<c_player>()) {
      // construct
      entity_t entity{};

      entity.player = ent;
      entity.pos = ent->central_position();

      entities.emplace_back(entity);
    }
  }

  // there are no entities in our vector
  if(entities.empty())
    return;

  for(const auto& ent : entities) {
    if(settings::visuals::esp::draw_players && ent.player->is_player()) {
      if(ent.player == ctx->local_player)
        continue;

      rect_t box{};

      if(!ent.player->calc_bounding_box(box))
        continue;

      const int x = box.x + (box.w / 2);
      int y = box.y + (box.h / 2);

      g_draw->string(g_draw->fonts[FONT_ESP], x, y, color(255, 255, 255, 255), e_text_align::TXT_LEFT, "Player");
    }

    if(settings::visuals::esp::draw_buildings && ent.player->is_building()) {
      rect_t box{};

      if(!ent.player->calc_bounding_box(box))
        continue;
    }
  }
}

bool c_esp::wants_render(c_entity* entity) {
  if(!entity || entity->is_dormant())
    return false;

  if(entity->is_player()) {
    if(settings::visuals::esp::draw_players) {
      if(entity == ctx->local_player || entity->is_dead())
        return false;
    }

  } else if (entity->is_building()) {
    if(!settings::visuals::esp::draw_buildings) {
      return true;
    }
  }
  return false;
}
