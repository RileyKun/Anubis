#pragma once

typedef unsigned long DWORD;

enum class font_flags : int {
  FONTFLAG_NONE,
  FONTFLAG_ITALIC = 0x001,
  FONTFLAG_UNDERLINE = 0x002,
  FONTFLAG_STRIKEOUT = 0x004,
  FONTFLAG_SYMBOL = 0x008,
  FONTFLAG_ANTIALIAS = 0x010,
  FONTFLAG_GAUSSIANBLUR = 0x020,
  FONTFLAG_ROTARY = 0x040,
  FONTFLAG_DROPSHADOW = 0x080,
  FONTFLAG_ADDITIVE = 0x100,
  FONTFLAG_OUTLINE = 0x200,
  FONTFLAG_CUSTOM = 0x400,
  FONTFLAG_BITMAP = 0x800,
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
  void  draw_set_color(color col);
  void  draw_filled_rect(int x, int y, int width, int height);
  void  draw_outlined_rect(int x, int y, int width, int height);
  void  draw_line(int x, int y, int width, int height);
  void  draw_set_text_font(DWORD font);
  void  draw_set_text_color(color col);
  void  draw_set_text_pos(int x, int y);
  void  draw_print_text(const char* text, int text_length);
  void  get_text_size(DWORD font, const char* text, int& wide, int& tall);
  void  set_cursor_visible(bool visible);
  bool  is_cursor_visible(void);
  void  play_sound(const char* name);
  DWORD create_font(void);
  void  set_font_glyph_set(DWORD& font, const char* name, int tall, int height, int blur,
                           int scan_lines, int flags);
};