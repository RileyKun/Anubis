#pragma once

class c_tf_player;
class c_base_entity;
struct rect_t;

class c_esp {
public:
  void run(c_tf_player* local);

private:
  static bool get_draw_bounds(c_base_entity* entity, rect_t& box);
};