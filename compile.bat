@echo off

if not exist build\ (
  mkdir build
)

cd build

if not exist CMakeFiles\ (
  cmake -G "MinGW Makefiles" ..
)

cmake --build .
pause