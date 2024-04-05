#pragma once

#include "typedefs.hpp"

#include <Windows.h>
#include <cstdint>

namespace memory{

  template<typename T>
  inline T find_interface(const char* module, const char* interface_name){
    // get a handle to the module
    if(const auto handle = GetModuleHandleA(module)){
      // get the exported function from the handle
      if (const auto interface_func = 
          reinterpret_cast<cint_fn>(GetProcAddress(handle, "CreateInterface"))){

        return reinterpret_cast<T>(interface_func(interface_name, nullptr));
      }
    }
    return T();
  }

  template<typename T>
  inline T find_vfunc(void* vmt, i32 index){
    return (*static_cast<T**>(vmt))[index]; // create an array of pointers
  }

  // find_vfunc but simplified, for use in hooks
  constexpr void* vfunc_ptr(void* vmt, i32 index){
    return (*static_cast<void***>(vmt))[index]; // create an array of pointer
  }

  // TODO: fix this.
  inline uintptr_t rel_to_abs(uintptr_t addr, ptrdiff_t displacement, ptrdiff_t next_addr){
    return reinterpret_cast<u64>(addr + displacement) + addr + next_addr;
  }
}