#include "drawsystem.hpp"

#include "link.hpp"

enum font_flags {
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
  fonts[FONT_WATERMARK] = {0x0, "Segoe UI", 18, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE};

  // iterate through fonts and create them in surface
  for(auto& cur_font : fonts) {
    cur_font.font = g_tf2.surface->create_font();
    g_tf2.surface->set_font_glyph_set(cur_font.font, cur_font.name, cur_font.tall, cur_font.weight,
                                      0, 0, cur_font.flags);
  }
}

// generic string no. 246
void c_draw::string(const font_t& font, int x, int y, const color& col, const e_text_align& align,
                    const char* input, ...) {
  va_list va_alist;
  char    buf[1024];

  va_start(va_alist, input);
  vsprintf_s(buf, input, va_alist);
  va_end(va_alist);

  switch(align) {
    case e_text_align::TXT_LEFT: {
      break;
    }
    case e_text_align::TXT_CENTER: {
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

  wchar_t wbuf[1024]{};
  MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), wbuf, sizeof(wbuf));

  g_tf2.surface->draw_set_text_pos(x, y);
  g_tf2.surface->draw_set_text_font(font.font);
  g_tf2.surface->draw_set_text_color(col);
  g_tf2.surface->draw_print_text(wbuf, wcslen(wbuf));
}
void c_draw::line(int x, int y, int w, int h, const color& col) {
  g_tf2.surface->draw_set_color(col);
  g_tf2.surface->draw_line(x, y, w, h);
}
void c_draw::rect(int x, int y, int w, int h, const color& col) {
  g_tf2.surface->draw_set_color(col);
  g_tf2.surface->draw_outlined_rect(x, y, w, h);
}
void c_draw::filled_rect(int x, int y, int w, int h, const color& col) {
  g_tf2.surface->draw_set_color(col);
  g_tf2.surface->draw_filled_rect(x, y, w, h);
}