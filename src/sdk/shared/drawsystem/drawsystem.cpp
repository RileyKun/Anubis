#include "drawsystem.hpp"

#include "link.hpp"

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

void c_draw::reload_fonts() {
  // set up fonts
  fonts[FONT_TEST] = {0x0, "DroidSans", 13, 600, 0x210};

  // iterate through fonts and create them in surface
  for(auto& cur_font : fonts) {
    cur_font.font = g_tf2.surface->create_font();
    g_tf2.surface->set_font_glyph_set(cur_font.font, cur_font.name, cur_font.tall, cur_font.weight, 0,
                                      0, cur_font.flags);
  }
}

// generic string no. 246
void c_draw::string(const font_t& font, int x, int y, const color& col, const e_text_align& align,
                    const char* input, ...) {
  va_list va_alist;
  char buf[1024];
  
  va_start(va_alist, input);
  vsprintf_s(buf, input, va_alist);
  va_end(va_alist);
  
  switch(align){
    case e_text_align::TXT_LEFT: {
      break;
    }
    case e_text_align::TXT_CENTER:{
      int w, h = 0;
      g_tf2.surface->get_text_size(font.font, buf, w, h);
      x -= (w / 2);
      break;
    }
    case e_text_align::TXT_RIGHT: {
      int w, h = 0;
      g_tf2.surface->get_text_size(font.font, buf, w, h);
      x -= w;
      break;
    }
  }
  
  g_tf2.surface->draw_set_text_pos(x, y);
  g_tf2.surface->draw_set_text_font(font.font);
  g_tf2.surface->draw_set_text_color(col);
  g_tf2.surface->draw_print_text(buf, strlen(buf));
}
void c_draw::line(int x, int y, int w, int h, const color& col) {
}
void c_draw::rect(int x, int y, int w, int h, const color& col) {
}
void c_draw::filled_rect(int x, int y, int w, int h, const color& col) {
}