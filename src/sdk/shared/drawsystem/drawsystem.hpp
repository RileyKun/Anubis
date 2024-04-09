#pragma once

#include "../typedefs.hpp"

#include <array>

class color;

struct font_t {
  DWORD       font = 0x0;
  const char* name = nullptr;
  int         tall{}, weight{}, flags{};
};

enum e_fonts {
  FONT_WATERMARK,
  FONT_END,
};

enum e_text_align {
  TXT_LEFT,
  TXT_CENTER,
  TXT_RIGHT,
};

class c_draw {
public:
  void reload_fonts();
  void string(const font_t& font, int x, int y, const color& col, const e_text_align& align,
              const char* input, ...);
  void line(int x, int y, int w, int h, const color& col);
  void rect(int x, int y, int w, int h, const color& col);
  void filled_rect(int x, int y, int w, int h, const color& col);
  std::array<font_t, FONT_END> fonts{};
};