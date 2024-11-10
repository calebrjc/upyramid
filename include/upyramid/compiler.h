#ifndef __UPYR_COMPILER_H__
#define __UPYR_COMPILER_H__

// Likely/Unlikely traits
#ifdef __GNUC__
#define UPYR_LIKELY(x)   __builtin_expect(!!(x), 1)
#define UPYR_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define UPYR_LIKELY(x)   (x)
#define UPYR_UNLIKELY(x) (x)
#endif

#endif  // __UPYR_COMPILER_H__
