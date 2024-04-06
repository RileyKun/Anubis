#include "surface.hpp"

#include "link.hpp"

void i_surface::draw_set_color(color col) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int, int, int)>(this, 11u)(this, col.R, col.G,
                                                                              col.B, col.A);
}

void i_surface::draw_filled_rect(int x, int y, int width, int height) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int, int, int)>(this, 12u)(this, x, y, width,
                                                                              height);
}

void i_surface::draw_outlined_rect(int x, int y, int width, int height) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int, int, int)>(this, 14u)(this, x, y, width,
                                                                              height);
}

void i_surface::draw_line(int x, int y, int width, int height) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int, int, int)>(this, 15u)(this, x, y, width,
                                                                              height);
}

void i_surface::draw_set_text_font(DWORD font) {
  memory::find_vfunc<void(__thiscall*)(void*, DWORD)>(this, 17u)(this, font);
}

void i_surface::draw_set_text_color(color col) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int, int, int)>(this, 19u)(this, col.R, col.G,
                                                                              col.B, col.A);
}

void i_surface::draw_set_text_pos(int x, int y) {
  memory::find_vfunc<void(__thiscall*)(void*, int, int)>(this, 20u)(this, x, y);
}

void i_surface::draw_print_text(const char* text, int text_length) {
  memory::find_vfunc<void(__thiscall*)(void*, const char*, int)>(this, 22u)(this, text,
                                                                            text_length);
}

void i_surface::get_text_size(DWORD font, const char* text, int& wide, int& tall) {
  memory::find_vfunc<void(__thiscall*)(void*, DWORD, const char*, int&, int&)>(this, 75u)(
      this, font, text, wide, tall);
}

void i_surface::set_cursor_visible(bool visible) {
  memory::find_vfunc<void(__thiscall*)(void*, bool)>(this, 52u)(this, visible);
}

bool i_surface::is_cursor_visible(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 53u)(this);
}

void i_surface::play_sound(const char* name) {
  memory::find_vfunc<void(__thiscall*)(void*, const char*)>(this, 78u)(this, name);
}

DWORD i_surface::create_font(void) {
  return memory::find_vfunc<DWORD(__thiscall*)(void*)>(this, 66u)(this);
}

void i_surface::set_font_glyph_set(DWORD& font, const char* name, int tall, int height, int blur,
                                   int scan_lines, int flags) {
  memory::find_vfunc<void(__thiscall*)(void*, DWORD&, const char*, int, int, int, int, int)>(
      this, 67u)(this, font, name, tall, height, blur, scan_lines, flags);
}