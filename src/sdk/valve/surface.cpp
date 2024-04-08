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

void i_surface::draw_print_text(const wchar_t* text, int text_length, FontDrawType_t drawType) {
  memory::find_vfunc<void(__thiscall*)(void*, const wchar_t*, int, FontDrawType_t)>(this, 22u)(
      this, text, text_length, drawType);
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

bool i_surface::set_font_glyph_set(DWORD font, const char* name, int tall, int weight, int blur,
                                   int scan_lines, int flags, int range_min, int range_max) {
  return memory::find_vfunc<bool(__thiscall*)(void*, DWORD, const char*, int, int, int, int, int,
                                              int, int)>(this, 67u)(
      this, font, name, tall, weight, blur, scan_lines, flags, range_min, range_max);
}

void i_surface::start() {
  typedef void(__thiscall * start_fn)(i_surface*);
  static auto start_ = memory::find_pattern<start_fn>(
      "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14");
  start_(this);
}

void i_surface::stop() {
  typedef void(__thiscall * stop_fn)(i_surface*);
  static auto stop_ = memory::find_pattern<stop_fn>(
      "vguimatsurface.dll",
      "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00");
  stop_(this);
}
