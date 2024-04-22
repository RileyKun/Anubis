@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

if not exist build\ (
  mkdir build
)

cd build

if not exist CMakeFiles\ (
  cmake -G "Ninja" ..
)

cmake --build .
pause