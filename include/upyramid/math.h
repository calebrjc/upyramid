#ifndef __UPYR_MATH_H__
#define __UPYR_MATH_H__

#define UPYR_MAX(_a, _b)            (((_a) >= (_b)) ? (_a) : (_b))
#define UPYR_MIN(_a, _b)            (((_a) <= (_b)) ? (_a) : (_b))
#define UPYR_ABS(_v)                (((_v) < 0) ? (-_v) : (_v))
#define UPYR_CLAMP(_x, _low, _high) (UPYR_MIN(_high, UPYR_MAX(_low, _x)))

#define UPYR_MAX_VAL(_bits)         (uint32_t)((1 << _bits) - 1)
#define UPYR_U8_MAX                 UPYR_MAX_VAL(8)
#define UPYR_U16_MAX                UPYR_MAX_VAL(16)
#define UPYR_U32_MAX                UPYR_MAX_VAL(32)
#define UPYR_U64_MAX                UPYR_MAX_VAL(64)

#endif  // __UPYR_MATH_H__
