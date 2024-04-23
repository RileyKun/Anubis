#include "drawsystem.hpp"

#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include "link.hpp"

// Initialize the drawsystem on the first frame of present.
void c_drawsystem::initialize(IDirect3DDevice9* device, HWND window) {
  ImGui::CreateContext();

  ImGuiIO io;
  io = ImGui::GetIO();
  io.IniFilename = nullptr;

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX9_Init(device);
}

// Start our frame and allow drawing.
void c_drawsystem::start_paint(IDirect3DDevice9* device) {
  // Disable color correction
  device->GetRenderState(D3DRS_SRGBWRITEENABLE, &m_prev_srgb);
  device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);

  // Start our frame
  ImGui_ImplDX9_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

// Finish our frame and send data.
void c_drawsystem::finish_paint(IDirect3DDevice9* device) {
  // End our frame and send data
  ImGui::Render();
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

  // Restore color correction
  device->SetRenderState(D3DRS_SRGBWRITEENABLE, m_prev_srgb);
}
// TODO: add font support
void c_render::string(ImDrawList* list, ImFont* font, int x, int y, bool outlined,
                      e_text_align align, ImColor col, const char* input) {
  if(!input) // we have no input, don't even bother trying
    return;

  // Get the text size
  ImVec2 size = ImGui::CalcTextSize(input, nullptr, true);
  float  left, top;

  // should we remove this?
  auto   f_x = static_cast<float>(x);
  auto   f_y = static_cast<float>(y);

  // Now run calculations
  switch(align) {
    case e_text_align::TEXT_LEFT: {
      break; // Do not change anything, left is the default alignment in ImGui
    }
    case e_text_align::TEXT_CENTER: {
      f_x -= size.x / 2; // move the text left by half of the size of the string
      break;
    }
    case e_text_align::TEXT_RIGHT: {
      f_x -= size.x; // move the text left by the entire size of the string
      break;
    }
    default:
      break;
  }

  // https://github.com/ocornut/imgui/issues/745
  if(outlined) {
    if(ctx->get_render_state()) {
      left = f_x + 1.f;
      top = f_y + 1.f;
      list->AddText({left, top}, ImColor(0.f, 0.f, 0.f, col.Value.w), input, nullptr);
    } else { // Because ImGui has no native method of doing outlines, we must draw the same text
             // four times to achieve an outline. If the user has optimized rendering on, then the
             // text will be a drop shadow instead of a full outline.
      left = f_x;
      top = f_y + 1.f;
      list->AddText({left, top}, ImColor(0.f, 0.f, 0.f, col.Value.w), input, nullptr);
      left = f_x + 1.f;
      top = f_y;
      list->AddText({left, top}, ImColor(0.f, 0.f, 0.f, col.Value.w), input, nullptr);
      left = f_x - 1.f;
      top = f_y;
      list->AddText({left, top}, ImColor(0.f, 0.f, 0.f, col.Value.w), input, nullptr);
      left = f_x;
      top = f_y - 1.f;
      list->AddText({left, top}, ImColor(0.f, 0.f, 0.f, col.Value.w), input, nullptr);
    }
  }
  left = f_x;
  top = f_y;
  list->AddText({left, top}, col, input, nullptr);
}

void c_render::circle(ImDrawList* list, int x, int y, float rad, bool outlined, ImColor col) {
  auto f_x = static_cast<float>(x);
  auto f_y = static_cast<float>(y);

  if(outlined && !ctx->get_render_state()) {
    list->AddCircle({f_x, f_y}, rad - 1.f, ImColor(0.f, 0.f, 0.f, col.Value.w));
    list->AddCircle({f_x, f_y}, rad + 1.f, ImColor(0.f, 0.f, 0.f, col.Value.w));
  }
  list->AddCircle({f_x, f_y}, rad, col);
}
void c_render::box(ImDrawList* list, int x, int y, int w, int h, bool outlined, ImColor col) {
  // lol
  auto f_x = static_cast<float>(x);
  auto f_y = static_cast<float>(y);
  auto f_w = static_cast<float>(w);
  auto f_h = static_cast<float>(h);

  if(outlined) {
    list->AddRect({f_x + 1.f, f_y + 1.f}, {f_x + f_w + 1.f, f_y + f_h + 1.f},
                  ImColor(0.f, 0.f, 0.f, col.Value.w));
    list->AddRect({f_x - 1.f, f_y - 1.f}, {f_x + f_w - 1.f, f_y + f_h - 1.f},
                  ImColor(0.f, 0.f, 0.f, col.Value.w));
  }
  list->AddRect({f_x, f_y}, {f_x + f_w, f_y + f_h}, col);
}

// ========================================
// Below starts the threaded functions.
// Unless you know what you are doing, do
// not edit them. If you need to make any
// changes, change the above functions, as
// they actually affect what is outputted
// to your screen.
//
// ~Riley
// ========================================

void c_render_threaded::string(ImFont* font, int x, int y, bool outlined, e_text_align align,
                               ImColor col, const char* input) {
  m_cmds.emplace_back(string_t{font, x, y, outlined, align, col, input});
}

void c_render_threaded::circle(int x, int y, float rad, bool outlined, ImColor col) {
  m_cmds.emplace_back(circle_t{x, y, rad, outlined, col});
}

void c_render_threaded::box(int x, int y, int width, int height, bool outlined, ImColor col) {
  m_cmds.emplace_back(box_t{x, y, width, height, outlined, col});
}

void c_render_threaded::flush() {
  {
    std::scoped_lock _{m_mutex}; // lock the mutex
    m_cmds.swap(m_safe_cmds);    // swap our existing commands to our safe command stack
  }

  m_cmds.clear(); // clear our stored commands, we do not need them anymore
}

void c_render_threaded::paint_traverse(ImDrawList* list) {
  std::scoped_lock _{m_mutex}; // unlock the mutex

  // now iterate through our commands
  for(auto&& cmds : m_safe_cmds) {
    // do not try to touch the if statements, these will not work otherwise if you do so
    if(auto* string = std::get_if<string_t>(&cmds)) {
      g_draw->string(list, string->font, string->x, string->y, string->outlined, string->align,
                     string->col, string->input);
    } else if(auto* box = std::get_if<box_t>(&cmds)) {
      g_draw->box(list, box->x, box->y, box->width, box->height, box->outlined, box->col);
    } else if(auto* circle = std::get_if<circle_t>(&cmds)) {
      g_draw->circle(list, circle->x, circle->y, circle->rad, circle->outlined, circle->col);
    }
  }
}
