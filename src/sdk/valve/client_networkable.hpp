#pragma once

#include "client_unknown.hpp"
#include "datatables.hpp"

#include "bitbuf.hpp"

#include "tf/tf_constants.hpp"

enum e_should_transmit_state {
  SHOULDTRANSMIT_START = 0,
  SHOULDTRANSMIT_END
};

enum e_data_update_type {
  DATA_UPDATE_CREATED = 0,
  DATA_UPDATE_DATATABLE_CHANGED,
};

class i_client_networkable {
public:
  virtual i_client_unknown* get_i_client_unknown() = 0;
  virtual void              release() = 0;
  virtual ClientClass*      get_client_class() = 0;
  virtual void              notify_should_transmit(e_should_transmit_state state) = 0;
  virtual void              on_pre_data_changed(e_data_update_type update_type) = 0;
  virtual void              on_data_changed(e_data_update_type update_type) = 0;
  virtual void              pre_data_update(e_data_update_type update_type) = 0;
  virtual void              post_data_update(e_data_update_type update_type) = 0;
  virtual bool              is_dormant(void) = 0;
  virtual int               entidx(void) const = 0;
  virtual void              receive_message(int class_id, bf_read& msg) = 0;
  virtual void*             get_data_table_base_ptr() = 0;
  virtual void              set_destroyed_on_recreate_entities(void) = 0;
  virtual void              on_data_unchanged_in_pvs() = 0;
  inline e_class_ids        get_class_id() {
    if(auto client_class = get_client_class())
      return static_cast<e_class_ids>(client_class->m_ClassID);

    return static_cast<e_class_ids>(0);
  }
};