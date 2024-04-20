cmake_minimum_required(VERSION 3.20)
project(Anubis LANGUAGES CXX)

# Statically link CRT if we are on clang-cl.
# Otherwise, the MSVC will take the /MT switch.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include CPM
include(CPM.cmake)

# TODO: Riley; add imgui
CPMAddPackage("gh:cursey/safetyhook@0.4.1")
# manual configuration required
CPMAddPackage(
  NAME zydis
  GITHUB_REPOSITORY zyantific/zydis
  VERSION 4.0.0
  OPTIONS "ZYDIS_BUILD_EXAMPLES OFF"
  "ZYDIS_BUILD_TOOLS OFF"
  "ZYDIS_BUILD_DOXYGEN OFF"
)

add_library(Anubis SHARED
  # cheat files
  src/entry_point.cpp
  src/factory/factory.cpp
  src/sdk/link.cpp
  # src/cheat/gui/watermark/watermark.cpp
  
  # game classes
  src/sdk/valve/netvars/netvars.cpp
  src/sdk/valve/tf/c_entity.cpp
  
  # interface map outs
  src/sdk/valve/engine_client.cpp
  src/sdk/valve/hl_client.cpp
  src/sdk/valve/surface.cpp
  src/sdk/valve/engine_vgui.cpp
  src/sdk/valve/render_view.cpp
  
  # hooks
  src/cheat/hooks/lists/createmove.cpp
  src/cheat/hooks/lists/fs_notify.cpp
  src/cheat/hooks/lists/present.cpp
  
  # features
  src/cheat/features/movement/movement.cpp
)

# allow fast includes of sdk
target_include_directories(Anubis PRIVATE src/sdk)

# allow fast includes of features
target_include_directories(Anubis PRIVATE src/cheat/features)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(Anubis PRIVATE
    NOMINMAX
  )
  target_compile_options(Anubis PRIVATE
    /Od # Disable optimizations
    /Zi # Generate debug info, do not allow edit and continue
    /MTd # Statically link a debug version of the CRT, DO NOT DISTRIBUTE.
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  target_compile_definitions(Anubis PRIVATE
    NOMINMAX
    NDEBUG
  )
  target_compile_options(Anubis PRIVATE
    /O2 # Enable optimizations
    /Zi # Generate debug info, do not allow edit and continue
    /MT # Statically link CRT.
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(Anubis PRIVATE
    NOMINMAX
    NDEBUG
  )
  target_compile_options(Anubis PRIVATE
    /O2 # Enable optimizations
    /MT # Statically link CRT.
  )
else()
  message(FATAL_ERROR "Your build type is not supported. Please check your toolchains and try again.")
endif()

# link safetyhook to our dll
target_link_libraries(Anubis PRIVATE safetyhook::safetyhook d3d9)