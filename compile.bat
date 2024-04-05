@echo off

if not exist build\ (
  mkdir build
)

cd build

if not exist CMakeFiles\ (
  cmake -G "Visual Studio 17 2022" ..
)

cmake --build .
pause