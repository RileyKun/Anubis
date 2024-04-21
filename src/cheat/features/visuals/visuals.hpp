#pragma once

class c_entity;

class c_esp {
private:
  bool get_bounds(c_entity* entity, int& x, int& y, int& w, int& h);
public:
  void run();
};

namespace f{
inline c_esp esp{};
}