#pragma once

#include "client_networkable.hpp"
#include "client_renderable.hpp"
#include "client_thinkable.hpp"

class c_mouth_info;
struct spatialization_info_t;

class i_client_entity : public i_client_unknown,
                        public i_client_renderable,
                        public i_client_networkable,
                        public i_client_thinkable {
public:
  virtual void                    release(void) = 0;
  virtual const Vector&           get_abs_origin(void) const = 0;
  virtual const QAngle&           get_abs_angles(void) const = 0;
  virtual c_mouth_info*           get_mouth(void) = 0;
  virtual bool                    get_sound_spatialization(spatialization_info_t& info) = 0;

  template <typename T> inline T* as() { return reinterpret_cast<T*>(this); }
};