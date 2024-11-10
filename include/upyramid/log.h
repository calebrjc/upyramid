#ifndef __UPYR_LOG_H__
#define __UPYR_LOG_H__

#include "upyramid/detail/common.h"

#define _UPYR_LOG_COLOR_DEFAULT "\033[39m"
#define _UPYR_LOG_COLOR_RED     "\033[91m"
#define _UPYR_LOG_COLOR_GRAY    "\033[90m"
#define _UPYR_LOG_COLOR_GREEN   "\033[92m"
#define _UPYR_LOG_COLOR_MAGENTA "\033[95m"
#define _UPYR_LOG_COLOR_YELLOW  "\033[93m"

typedef enum
{
    UPYR_LOG_LEVEL_DEBUG = 0,
    UPYR_LOG_LEVEL_INFO,
    UPYR_LOG_LEVEL_WARN,
    UPYR_LOG_LEVEL_ERROR,
    UPYR_LOG_LEVEL_NOTIFICATION,
} upyr_log_level_e;

typedef int upyr_log_tag_t;

typedef void (*upyr_log_putchar_f)(void *arg, char c, bool flush);
typedef const char *(*upyr_log_validation_callback_f)(upyr_log_tag_t tag);

int upyr_log_init(upyr_log_putchar_f puchar_func, void *putchar_arg);

void upyr_log_set_level(upyr_log_level_e level);

void upyr_log_set_validation_callback(upyr_log_validation_callback_f validation_callback_func);

void _upyr_log_generic(
    upyr_log_tag_t   tag,
    upyr_log_level_e level,
    const char      *file,
    int              line,
    const char      *color,
    const char      *prefix,
    const char      *postfix,
    const char      *format,
    ...);

void _upyr_log_hex_generic(
    upyr_log_tag_t   tag,
    upyr_log_level_e level,
    const char      *file,
    int              line,
    const char      *color,
    const char      *prefix,
    const void      *data,
    size_t           size,
    const char      *user_prefix);

#define _UPYR_LOG_IMPL(_tag, _level, _color, _prefix, _postfix, ...)                               \
    _upyr_log_generic(_tag, _level, __FILE__, __LINE__, _color, _prefix, _postfix, ##__VA_ARGS__)

#define _UPYR_LOG_HEX_IMPL(_tag, _level, _color, _prefix, _data, _size, _user_prefix)              \
    _upyr_log_hex_generic(                                                                         \
        _tag, _level, __FILE__, __LINE__, _color, _prefix, _data, _size, _user_prefix)

// -------------------------------------------------------------------------------------------------

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL_DEBUG(_tag, ...)                                                              \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_DEBUG, _UPYR_LOG_COLOR_GRAY, "D", "", ##__VA_ARGS__)

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL_INFO(_tag, ...)                                                               \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_INFO, _UPYR_LOG_COLOR_GREEN, "I", "", ##__VA_ARGS__)

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL_WARN(_tag, ...)                                                               \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_WARN, _UPYR_LOG_COLOR_YELLOW, "W", "", ##__VA_ARGS__)

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL_ERROR(_tag, ...)                                                              \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_ERROR, _UPYR_LOG_COLOR_RED, "E", "", ##__VA_ARGS__)

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL_NOTIFICATION(_tag, ...)                                                       \
    _UPYR_LOG_IMPL(                                                                                \
        _tag, UPYR_LOG_LEVEL_NOTIFICATION, _UPYR_LOG_COLOR_MAGENTA, "!", "", ##__VA_ARGS__)

/// @brief Print a log.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NNL(_tag, ...) UPYR_LOG_NNL_INFO(_tag, ##__VA_ARGS__)

// -------------------------------------------------------------------------------------------------

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_DEBUG(_tag, ...)                                                                  \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_DEBUG, _UPYR_LOG_COLOR_GRAY, "D", "\n", ##__VA_ARGS__)

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_INFO(_tag, ...)                                                                   \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_INFO, _UPYR_LOG_COLOR_GREEN, "I", "\n", ##__VA_ARGS__)

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_WARN(_tag, ...)                                                                   \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_WARN, _UPYR_LOG_COLOR_YELLOW, "W", "\n", ##__VA_ARGS__)

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_ERROR(_tag, ...)                                                                  \
    _UPYR_LOG_IMPL(_tag, UPYR_LOG_LEVEL_ERROR, _UPYR_LOG_COLOR_RED, "E", "\n", ##__VA_ARGS__)

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG_NOTIFICATION(_tag, ...)                                                           \
    _UPYR_LOG_IMPL(                                                                                \
        _tag, UPYR_LOG_LEVEL_NOTIFICATION, _UPYR_LOG_COLOR_MAGENTA, "!", "\n", ##__VA_ARGS__)

/// @brief Print a log with a trailing newline.
/// @param _tag The tag to print the log under.
/// @param ... Printf-style arguments to format the log message.
#define UPYR_LOG(_tag, ...) UPYR_LOG_INFO(_tag, ##__VA_ARGS__)

// -------------------------------------------------------------------------------------------------

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX_DEBUG(_tag, _data, _size, _prefix)                                            \
    _UPYR_LOG_HEX_IMPL(_tag, UPYR_LOG_LEVEL_DEBUG, _UPYR_LOG_COLOR_GRAY, "D", _data, _size, _prefix)

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX_INFO(_tag, _data, _size, _prefix)                                             \
    _UPYR_LOG_HEX_IMPL(_tag, UPYR_LOG_LEVEL_INFO, _UPYR_LOG_COLOR_GREEN, "I", _data, _size, _prefix)

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX_WARN(_tag, _data, _size, _prefix)                                             \
    _UPYR_LOG_HEX_IMPL(                                                                            \
        _tag, UPYR_LOG_LEVEL_WARN, _UPYR_LOG_COLOR_YELLOW, "W", _data, _size, _prefix)

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX_ERROR(_tag, _data, _size, _prefix)                                            \
    _UPYR_LOG_HEX_IMPL(_tag, UPYR_LOG_LEVEL_ERROR, _UPYR_LOG_COLOR_RED, "E", _data, _size, _prefix)

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX_NOTIFICATION(_tag, _data, _size, _prefix)                                     \
    _UPYR_LOG_HEX_IMPL(                                                                            \
        _tag, UPYR_LOG_LEVEL_NOTIFICATION, _UPYR_LOG_COLOR_MAGENTA, "!", _data, _size, _prefix)

/// @brief Print a series of logs which print the contents of some memory in a hexdump-like
/// format.
/// @param _tag The tag to print the log under.
/// @param _data The data to log.
/// @param _size The size of the data to log.
/// @param _prefix Optional; The prefix to use for each line of output.
#define UPYR_LOG_HEX(_tag, _data, _size, _prefix) UPYR_LOG_HEX_INFO(_tag, _data, _size, _prefix)

#endif  // __UPYR_LOG_H__
