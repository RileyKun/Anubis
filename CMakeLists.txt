cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Anubis LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

# Fetch CPM
set(CPM_DOWNLOAD_VERSION 0.38.7)
set(CPM_HASH_SUM "83e5eb71b2bbb8b1f2ad38f1950287a057624e385c238f6087f94cdfc44af9c5")

if(CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
  set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
  set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

if(NOT EXISTS ${CPM_DL_LOCATION})
  message(STATUS "Downloading CPM.cmake to: ${CPM_DOWNLOAD_LOCATION}")
  
  file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION})

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
  src/sdk/shared/drawsystem/drawsystem.cpp
  src/cheat/gui/watermark/watermark.cpp
  
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
  src/cheat/hooks/lists/paint.cpp
  
  # features
  src/cheat/features/movement/movement.cpp
  src/cheat/features/visuals/visuals/esp.cpp
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
    /Od # disable optimizations
    /Zi # generate debug info, do not allow edit and continue
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  target_compile_definitions(Anubis PRIVATE
    NOMINMAX
    NDEBUG
  )
  target_compile_options(Anubis PRIVATE
    /O2 # enable optimizations
    /Zi # Generate debug info, do not allow edit and continue
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(Anubis PRIVATE
    NOMINMAX
    NDEBUG
  )
  target_compile_options(Anubis PRIVATE
    /O2
  )
else()
  message(FATAL_ERROR "Your build type is not supported. Please check your toolchains and try again.")
endif()

# link safetyhook to our dll
target_link_libraries(Anubis PRIVATE safetyhook::safetyhook)