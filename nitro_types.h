#ifndef NITRO_TYPES_H
#define NITRO_TYPES_H

#include <stdint.h>

typedef uint8_t       u8;
typedef uint16_t      u16;
typedef uint32_t      u32;
typedef int8_t        s8;
typedef int16_t       s16;
typedef int32_t       s32;
typedef uint64_t      u64;
typedef int64_t       s64;
typedef volatile u8   vu8;
typedef volatile u16  vu16;
typedef volatile u32  vu32;
typedef volatile u64  vu64;
typedef volatile s8   vs8;
typedef volatile s16  vs16;
typedef volatile s32  vs32;
typedef volatile s64  vs64;
typedef float         f32;
typedef volatile f32  vf32;
typedef u8            REGType8;
typedef u16           REGType16;
typedef u32           REGType32;
typedef u64           REGType64;
typedef vu8           REGType8v;
typedef vu16          REGType16v;
typedef vu32          REGType32v;
typedef vu64          REGType64v;
typedef int           BOOL;

#define TRUE   (1)
#define FALSE  (0)

#define NULL  ((void *)0)

#endif
