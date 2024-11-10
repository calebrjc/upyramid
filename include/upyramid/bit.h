#ifndef __UPYR_BIT_H__
#define __UPYR_BIT_H__

#define UPYR_LITTLE_ENDIAN 1234
#define UPYR_BIG_ENDIAN    4321

#include "upyramid/detail/common.h"

#if __has_include("endian.h")
#include <endian.h>
#else
#if !defined(_BYTE_ORDER) && !defined(UPYR_BYTE_ORDER)                                             \
    || (UPYR_BYTE_ORDER != UPYR_BIG_ENDIAN && UPYR_BYTE_ORDER != UPYR_LITTLE_ENDIAN)
#error No endianness defined. Please define UPYR_BYTE_ORDER as UPYR_LITTLE_ENDIAN or UPYR_BIG_ENDIAN
#else
#include <stdint.h>

static inline uint16_t __bswap16(uint16_t x)
{
    return (uint16_t)((x >> 8) | ((x << 8) & 0xff00));
}

static inline uint32_t __bswap32(uint32_t x)
{
    return (uint32_t)((x >> 24) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000)
                      | ((x << 24) & 0xff000000));
}

#if UPYR_BYTE_ORDER == UPYR_LITTLE_ENDIAN
#define __htonl(_x) __bswap32(_x)
#define __htons(_x) __bswap16(_x)
#define __ntohl(_x) __bswap32(_x)
#define __ntohs(_x) __bswap16(_x)
#else
#define __htonl(_x) ((uint32_t)(_x))
#define __htons(_x) ((uint16_t)(_x))
#define __ntohl(_x) ((uint32_t)(_x))
#define __ntohs(_x) ((uint16_t)(_x))
#endif  // _BYTE_ORDER == _LITTLE_ENDIAN
#endif  // _BYTE_ORDER
#endif  // __has_include

#define UPYR_BIT(_n)           (1UL << (_n))
#define UPYR_BITSET(_v, _m)    (_v) |= (_m)
#define UPYR_BITCLEAR(_v, _m)  (_v) &= ~(_m)
#define UPYR_BITTOGGLE(_v, _m) (_v) ^= (_m)

#define UPYR_BSWAP16(_v)       __bswap16(_v)
#define UPYR_BSWAP32(_v)       __bswap32(_v)

#define UPYR_HTONS(_v)         __htons(_v)
#define UPYR_NTOHS(_v)         __ntohs(_v)
#define UPYR_HTONL(_v)         __htonl(_v)
#define UPYR_NTOHL(_v)         __ntohl(_v)

#endif  //  __UPYR_BIT_H__
