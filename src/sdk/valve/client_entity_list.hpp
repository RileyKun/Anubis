#pragma once

class i_client_entity;
class i_client_networkable;
class i_client_unknown;

using c_base_handle = unsigned int;

// ripped from the hl2src leak
class i_handle_entity {
public:
  virtual ~i_handle_entity() {}
  virtual void                 set_ref_e_handle(const c_base_handle& handle) = 0;
  virtual const c_base_handle& get_ref_e_handle() const = 0;
};

class i_client_entity_list {
public:
  virtual i_client_networkable* get_client_networkable(int ent_num) = 0;
  virtual i_client_networkable* get_client_networkable_from_handle(c_base_handle ent) = 0;
  virtual i_client_unknown*     get_client_unknown_from_handle(c_base_handle ent) = 0;
  virtual i_client_entity*      get_client_entity(int ent_num) = 0;
  virtual i_client_entity*      get_client_entity_from_handle(c_base_handle ent) = 0;
  virtual int                   number_of_entities(bool include_non_networked) = 0;
  virtual int                   get_highest_ent_index(void) = 0;
  virtual void                  get_max_entities(int max_ents) = 0;
  virtual int                   get_max_entities() = 0;
};