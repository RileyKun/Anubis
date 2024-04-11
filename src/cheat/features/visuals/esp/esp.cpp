#include "esp.hpp"

#include "config.hpp"
#include "link.hpp"

void c_esp::run(c_tf_player* local) {
  if(!settings::visuals::esp::enabled)
    return;
  
  rect_t bounds{};
  
  for(int ent = 1; ent <= g_tf2.entity_list->get_highest_ent_index(); ++ent) {
    i_client_entity* entity = g_tf2.entity_list->get_client_entity(ent);
    
    if(!entity || entity->is_dormant())
      continue;
    
    ClientClass* client_class = entity->get_client_class();
    
    if(!client_class)
      continue;
    
    switch(client_class->get_tf_class()){
      case e_class_ids::CTFPlayer: {
        if(!settings::visuals::esp::draw_players)
          break;
        
        auto player = entity->as<c_tf_player>();
        
        // TODO: Implement team check
        if(player->is_dead())
          break;
        
        
      }
      default: break;
    }
  }
}
bool c_esp::get_draw_bounds(c_base_entity* entity, rect_t& box) {
  return false;
}
