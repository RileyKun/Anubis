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
  void draw_set_color(const color& col);
  void draw_filled_rect(int x, int y, int width, int height);
  void draw_outlined_rect(int x, int y, int width, int height);
  void draw_line(int x, int y, int width, int height);
  void draw_set_text_font(DWORD font);
  void draw_set_text_color(const color& col);
  void draw_set_text_pos(int x, int y);
  void draw_print_text(const wchar_t* text, int text_length,
                        e_draw_type   draw_type = FONT_DRAW_DEFAULT);
  void  get_text_size(DWORD font, const char* text, int& wide, int& tall);
  void  set_cursor_visible(bool visible);
  bool  is_cursor_visible(void);
  void  play_sound(const char* name);
  DWORD create_font(void);
  bool  set_font_glyph_set(DWORD font, const char* name, int tall, int weight, int blur,
                           int scan_lines, int flags, int range_min = 0, int range_max = 0);
  void  start();
  void  stop();
};