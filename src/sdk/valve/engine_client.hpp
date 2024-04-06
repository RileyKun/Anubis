#pragma once

#include "mathlib.hpp"

class c_engine_client {
public:
  void get_screen_size(int& w, int& h);
  void client_cmd(const char* input);
  void client_cmd_unrestricted(const char* input);
  int get_local_player(void);
  float plat_float_time(void);
  void get_view_angles(QAngle& va);
  void set_view_angles(QAngle& va);
  int get_max_clients(void);
  // is not loading anymore but is connected
  bool is_in_game(void);
  // is connected but still loading
  bool is_connected(void);
  // returns the game's root directory
  const char* get_game_directory(void);
  const matrix3x4& world_to_screen_matrix(void);
};