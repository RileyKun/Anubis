#include <Windows.h>

#include "factory/factory.hpp"

DWORD __stdcall entry(void* arg) {
  while(!GetModuleHandleA("mss32.dll"))
    Sleep(150);

  factory->startup();

  while(!GetAsyncKeyState(VK_F6))
    Sleep(150);

  factory->shutdown();

  FreeLibraryAndExitThread(static_cast<HMODULE>(arg), 0);
}

DWORD __stdcall exit() {
  factory->shutdown();

  return 0;
}

int __stdcall DllMain(HMODULE inst, DWORD reason, void* arg) {
  switch(reason) {
    case DLL_PROCESS_ATTACH: {
      HANDLE thread = CreateThread(nullptr, 0, entry, inst, 0, nullptr);
      if(!thread) // thread doesn't exist
        return 0;
      
      // handle is no longer needed
      CloseHandle(thread);
      return 1;
    }
    case DLL_PROCESS_DETACH: {
      exit();
      return 1;
    }
    default:
      return 1;
  }
}