#pragma once

#include "link.hpp"


class c_esp {
private:
  struct entity_t {
    c_entity* player = nullptr;
    vec3 pos = vec3_t();
  };

  bool wants_render(c_entity* entity);
public:
  // NOTE: Riley; Storing entities like this in a vector could hit performance.
  // TODO: Change this off of a vector.
  std::vector<entity_t> entities = {};

  void run();
};


namespace f {
inline c_esp esp{};
}