#pragma once

#include "../typedefs.hpp"

#include <memory>

#include <string>
#include <string_view>

enum class e_icon_type : u16 {
  CON_OK = 10,
  CON_STAGE = 6,
  CON_WARN = 14,
  CON_ERROR = 12,
  CON_DEBUG = 9,
  CON_TEXT = 7,
  CON_TEXT_DIM = 8,
  CON_UNKNOWN = 5
};

class c_console {
public:
  void               print(e_icon_type icon_type, std::string_view input, ...) noexcept;
  void               spawn(std::string_view window) noexcept;
  void               kill() noexcept;
  [[nodiscard]] bool get_visible() const noexcept;

private:
  bool               is_open = false;
  std::string        title{};
  static std::string icon(e_icon_type icon) noexcept;
  void               set_color(e_icon_type col);
};
