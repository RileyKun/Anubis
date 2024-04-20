#pragma once

typedef unsigned long DWORD;

enum e_draw_type : int {
  FONT_DRAW_DEFAULT = 0,
  FONT_DRAW_NONADDITIVE,
  FONT_DRAW_ADDITIVE,
  FONT_DRAW_TYPE_COUNT = 2,
};

class color {
public:
  int R, G, B, A;

  color(int r, int g, int b, int a) {
    R = r;
    G = g;
    B = b;
    A = a;
  }
};

class i_surface {
public:
  void  set_cursor_visible(bool visible);
  bool  is_cursor_visible(void);
  void  play_sound(const char* name);
};