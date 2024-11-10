#ifndef __UPYR_ASSERT_H__
#define __UPYR_ASSERT_H__

#include "upyramid/compiler.h"
#include "upyramid/log.h"

void upyr_crash(void);

/// @brief Trigger a crash with an error message. Requires `upyr_platform_crash()` to be defined.
/// @param _format The `printf` format of the message.
/// @param ... The arguments for the message.
#define UPYR_CRASH(_format, ...)                                                                   \
    do                                                                                             \
    {                                                                                              \
        /* TODO(Caleb): Create "UPYR_CRASH tag" */                                                 \
        UPYR_LOG_ERROR(0, "Crash triggered - " _format, ##__VA_ARGS__);                            \
        upyr_crash();                                                                              \
    } while (0)

/// @brief Return from a function (optionally with a value) if the given condition is false.
/// @note Think about the condition as an assert condition.
/// @param _cond The condition to check.
/// @param ... Optional; The value to return if the condition is false.
#define UPYR_RETURN_IF_FALSE(_cond, ...)                                                           \
    do                                                                                             \
    {                                                                                              \
        if (UPYR_UNLIKELY(!(_cond)))                                                               \
        {                                                                                          \
            return __VA_ARGS__;                                                                    \
        }                                                                                          \
    } while (0)

/// @brief Return from a function (optionally with a value) if the given condition is true.
/// @param _cond The condition to check.
/// @param ... Optional; The value to return if the condition is true.
#define UPYR_RETURN_IF_TRUE(_cond, ...) UPYR_RETURN_IF_FALSE(!(_cond), ##__VA_ARGS__)

/// @brief If the given condition is false, print an error log with the given format and arguments
/// and return (optionally with a value).
/// @param _cond The condition to check.
/// @param _retval Optional; The value to return if the condition is false.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_ERROR_IF_FALSE(_cond, _retval, _format, ...)                                          \
    do                                                                                             \
    {                                                                                              \
        if (UPYR_UNLIKELY(!(_cond)))                                                               \
        {                                                                                          \
            /* TODO(Caleb): Create "UPYR_CHECK tag" */                                             \
            UPYR_LOG_ERROR(0, "Early return - error: " _format, ##__VA_ARGS__);                    \
            return _retval;                                                                        \
        }                                                                                          \
    } while (0)

/// @brief If the given condition is true, print an error log with the given format and arguments
/// and return (optionally with a value).
/// @param _cond The condition to check.
/// @param _retval Optional; The value to return if the condition is true.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_ERROR_IF_TRUE(_cond, _retval, _format, ...)                                           \
    UPYR_ERROR_IF_FALSE(!(_cond), _retval, _format, ##__VA_ARGS__)

/// @brief If the given condition is false, print an error log with the given format and
/// arguments.
/// @note Think of the condition as an assert condition.
/// @param _cond The condition to check.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_CHECK(_cond, _format, ...)                                                            \
    do                                                                                             \
    {                                                                                              \
        if (UPYR_UNLIKELY(!(_cond)))                                                               \
        {                                                                                          \
            /* TODO(Caleb): Create "UPYR_CHECK tag" */                                             \
            UPYR_LOG_ERROR(0, "Check failed (%s) - " _format, #_cond, ##__VA_ARGS__);              \
        }                                                                                          \
    } while (0)

#ifdef UPYR_DEBUG
/// @brief If the given condition is false, print an error log with the given format and
/// arguments.
/// @note Think of the condition as an assert condition.
/// @note This condition will not be evaluated in non-debug builds.
/// @param _cond The condition to check.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_DCHECK(_cond, _format, ...) UPYR_CHECK(_cond, _format, ##__VA_ARGS__)
#else
#define UPYR_DCHECK(...)
#endif

/// @brief If the given condition is false, print an error log with the given format and
/// arguments, then crash the processor. Requires `upyr_platform_crash()` to be defined.
/// @note Think of the condition as an assert condition.
/// @param _cond The condition to check.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_ASSERT(_cond, _format, ...)                                                           \
    do                                                                                             \
    {                                                                                              \
        if (UPYR_UNLIKELY(!(_cond)))                                                               \
        {                                                                                          \
            /* TODO(Caleb): Create "UPYR_ASSERT tag" */                                            \
            UPYR_LOG_ERROR(0, "Assert failed (%s) - " _format, #_cond, ##__VA_ARGS__);             \
            upyr_platform_crash();                                                                 \
        }                                                                                          \
    } while (0)

#ifdef UPYR_DEBUG
/// @brief If the given condition is false, print an error log with the given format and
/// arguments, then crash the processor. Requires `upyr_platform_crash()` to be defined.
/// @note Think of the condition as an assert condition.
/// @note This condition will not be evaluated in non-debug builds.
/// @param _cond The condition to check.
/// @param _format The message format.
/// @param ... The arguments for the message format.
#define UPYR_DASSERT(_cond, _format, ...) UPYR_ASSERT(_cond, _format, ##__VA_ARGS__)
#else
#define UPYR_DASSERT(...)
#endif
#endif  //  __UPYR_ASSERT_H__
