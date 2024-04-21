#include "../hooks.hpp"

#include <shared_mutex>
#include <wrl.h>

#include <safetyhook.hpp>

#include "link.hpp"

#include "../../gui/gui.hpp"

std::once_flag has_init;

template <typename T> using com_ptr = Microsoft::WRL::ComPtr<T>;

SafetyHookInline present{};
SafetyHookInline size{};

// FIXME: Riley; We may have to re-hook OnScreenSizeChanged or make a console command
// to reload the drawsystem when our screen resolution changes.
// The reason for this is because we cannot hook Reset() using this method of getting the game's
// device, as the device will be a nullptr when reset was called.
void             hooks::directx::startup() {
  // ComPtr the DirectX object as we don't need it after we get the device
  com_ptr<IDirect3D9> d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

  // get the game window
  auto window = FindWindowA("Valve001", nullptr); // this will work on all source games

  // set up some basic parameters, doesn't really matter what they are
  D3DPRESENT_PARAMETERS params{
                  .BackBufferFormat = D3DFMT_UNKNOWN,
                  .SwapEffect = D3DSWAPEFFECT_DISCARD,
                  .Windowed = TRUE,
                  .EnableAutoDepthStencil = TRUE,
                  .AutoDepthStencilFormat = D3DFMT_D16,
                  .PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT,
  };

  // com_ptr our device, we will trash this one the hook is created
  com_ptr<IDirect3DDevice9> d3d_device{};

  // create the device, this will return the game's device when we hook the method
  d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &d3d_device);

  // now create our detour, we must use .Get on the device as the singleton is out of scope
  present = safetyhook::create_inline(memory::vfunc_ptr(d3d_device.Get(), 17),
                                                  reinterpret_cast<void*>(hooked_present));
}

void hooks::directx::shutdown() {
  present = {};
}

HRESULT __stdcall hooks::directx::hooked_present(IDirect3DDevice9* device, const RECT* src,
                                                 const RECT* dest, HWND window,
                                                 const RGNDATA* dirty) {
  std::call_once(has_init, [&] {
    g_tf2.engine_client->get_screen_size(ctx->screen_width, ctx->screen_height);

    D3DDEVICE_CREATION_PARAMETERS params{};
    device->GetCreationParameters(&params);

    drawsystem->initialize(device, params.hFocusWindow);
  });

  drawsystem->start_paint(device);
  {
    auto* list = ImGui::GetBackgroundDrawList();

    g_draw_threaded.paint_traverse(list);
  }
  drawsystem->finish_paint(device);
  // Drawing is finished, call original.
  return present.stdcall<HRESULT>(device, src, dest, window, dirty);
}

void hooks::paint::startup() {
  size = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.surface, 111), hooked_size_changed);
}

void hooks::paint::hooked_size_changed(void* ecx, void* edx, int old_width, int old_height) {
  directx::shutdown();
  size.thiscall<void>(ecx, old_width, old_height);
  directx::startup();
  g_tf2.engine_client->get_screen_size(ctx->screen_width, ctx->screen_height);
}