#pragma once

typedef char                 i8;
typedef short               i16;
typedef int                 i32;
typedef long long           i64;

typedef unsigned char        u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef unsigned long     DWORD;

typedef void* (*cint_fn)(const char* name, int* return_code);