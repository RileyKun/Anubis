#pragma once

#include "datatables.hpp"
#include "frame_stage.hpp"
#include "view_setup.hpp"

class c_hl_client {
public:
  ClientClass* get_all_classes(void);
  bool get_player_view(c_view_setup& player_view);
};