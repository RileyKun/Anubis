#include "factory.hpp"

void c_factory::startup() {
  interfaces();
  hooks(true);
}

void c_factory::shutdown() {
  hooks(false);
}

void c_factory::hooks(bool startup) {
  if(startup) {

  } else {
  }
}

void c_factory::interfaces() {
}