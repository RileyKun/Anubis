#include "netvars.hpp"

#include "hash.hpp"
#include "link.hpp"

// credits: spook953
int c_netvars::get_netvar(const char* dt_class, const char* var) {
  ClientClass* classes = g_tf2.hl_client->get_all_classes(); // grab our classes

  // now iterate through the tables of our classes
  for(auto node = classes; node; node = node->m_pNext) {
    auto table = node->m_pRecvTable;
    // we found the table, get it's offset
    if(HASH_RT(dt_class) == HASH_RT(table->m_pNetTableName)) {
      return get_offset(table, var);
    }
  }
  return 0;
}

int c_netvars::get_offset(RecvTable* data_table, const char* var) {
  // iterate through props
  for(int i = 0; i < data_table->m_nProps; i++) {
    auto prop = &data_table->m_pProps[i];

    // found, return it's offset
    if(HASH_RT(prop->m_pVarName) == HASH_RT(var)) {
      return prop->m_Offset;
    }

    // credits: D3X
    if(prop->m_RecvType == DPT_DataTable) {

      if(auto child_table = prop->m_pDataTable) {
        // this looks confusing here, should we clean it up?
        if(auto offset = get_offset(child_table, var)) {
          return offset + prop->m_Offset;
        }
      }
    }
  }
  return 0;
}