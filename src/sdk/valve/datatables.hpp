#pragma once

// partial credits for minifying these classes goes to cleric @ ateris.tech

// ================
// dt_common.hpp
// ================
typedef enum {
  DPT_Int = 0,
  DPT_Float,
  DPT_Vector,
  DPT_VectorXY,
  DPT_String,
  DPT_Array,
  DPT_DataTable,
  DPT_NUMSendPropTypes
} SendPropType;

class DVariant {
public:
  DVariant() { m_Type = DPT_Float; }
  DVariant(float val) {
    m_Type = DPT_Float;
    m_Float = val;
  }

  union {
    float       m_Float;
    int         m_Int;
    const char* m_pString;
    void*       m_pData; // For DataTables.
    float       m_Vector[3];
  };
  SendPropType m_Type;
};

// ================
// dt_recv.hpp
// ================

class RecvTable;
class RecvProp;
class CRecvProxyData {
public:
  const RecvProp* m_pRecvProp; // The property it's receiving.
  DVariant        m_Value;     // The value given to you to store.
  int             m_iElement;  // Which array element you're getting.
  int             m_ObjectID;  // The object being referred to.
};

class CRecvDecoder;

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData,
                                        int objectID);

class RecvProp {
public:
  const char*             m_pVarName;
  SendPropType            m_RecvType;
  int                     m_Flags;
  int                     m_StringBufferSize;
  bool                    m_bInsideArray;

  const void*             m_pExtraData;

  RecvProp*               m_pArrayProp;
  ArrayLengthRecvProxyFn  m_ArrayLengthProxy;

  RecvVarProxyFn          m_ProxyFn;
  DataTableRecvVarProxyFn m_DataTableProxyFn;

  RecvTable*              m_pDataTable;
  int                     m_Offset;

  int                     m_ElementStride;
  int                     m_nElements;

  const char*             m_pParentArrayPropName;
};

class RecvTable {
public:
  typedef RecvProp PropType;

  RecvProp*        m_pProps;
  int              m_nProps;
  CRecvDecoder*    m_pDecoder;
  const char*      m_pNetTableName;

  bool             m_bInitialized;
  bool             m_bInMainList;
};

// ================
// client_class.hpp
// ================
typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();
class ClientClass {
public:
  CreateClientClassFn m_pCreateFn;
  CreateEventFn       m_pCreateEventFn; // Only called for event objects.
  const char*         m_pNetworkName;
  RecvTable*          m_pRecvTable;
  ClientClass*        m_pNext;
  int                 m_ClassID; // Managed by the engine.
};