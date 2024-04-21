#include "console.hpp"

#include <Windows.h>
#include <iostream>

void c_console::print(e_icon_type icon_type, std::string_view input, ...) noexcept {
  if(!get_visible() || input.empty())
    return;

  // color the braces, de-color the icon and restore for text
  // ... because multicolor looked fancier than a single color
  set_color(icon_type);
  std::cout << "[";

  set_color(e_icon_type::CON_TEXT);
  std::cout << icon(icon_type).c_str();

  set_color(icon_type);
  std::cout << "] ";

  set_color(e_icon_type::CON_TEXT);
  std::cout << input.data() << "\n";
}

void c_console::spawn(std::string_view window) noexcept {
  if(!AllocConsole())
    return;

  FILE* f{};

  freopen_s(&f, "CONIN$", "r", stdin);
  freopen_s(&f, "CONOUT$", "w", stdout);
  freopen_s(&f, "CONOUT$", "w", stderr);

  SetConsoleTitleA(window.data());

  this->title = window;
  this->is_open = true;
}

void c_console::kill() noexcept {
  if(!this->is_open)
    return;

  FreeConsole();
  HWND console = FindWindowA(nullptr, this->title.c_str());
  PostMessageA(console, WM_QUIT, 0, 0);
}

bool c_console::get_visible() const noexcept {
  return this->is_open;
}

std::string c_console::icon(e_icon_type icon) noexcept {
  switch(icon) {
    case e_icon_type::CON_OK:
      return "+";
    case e_icon_type::CON_STAGE:
    case e_icon_type::CON_WARN:
    case e_icon_type::CON_DEBUG:
      return "!";
    case e_icon_type::CON_ERROR:
      return "X";
    case e_icon_type::CON_TEXT:
    case e_icon_type::CON_TEXT_DIM:
    case e_icon_type::CON_UNKNOWN:
      return "?";
  }
  std::unreachable();
}

void c_console::set_color(e_icon_type col) {
  SetConsoleTextAttribute(GetStdHandle(static_cast<DWORD>(-11)), *reinterpret_cast<WORD*>(&col));
}
