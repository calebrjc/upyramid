#include "upyramid/log.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#include "upyramid/assert.h"
#include "upyramid/math.h"

// TODO(Caleb): Do I need to lock this module?

// -------------------------------------------------------------------------------------------------

static upyr_log_putchar_f             s_putchar             = NULL;
static void                          *s_putchar_arg         = NULL;
static upyr_log_level_e               s_level               = UPYR_LOG_LEVEL_DEBUG;
static upyr_log_validation_callback_f s_validation_callback = NULL;

// -------------------------------------------------------------------------------------------------

static void _upyr_log_puts(const char *s);
static void _upyr_log_printf(const char *format, ...);

// -------------------------------------------------------------------------------------------------

int upyr_log_init(upyr_log_putchar_f putchar_func, void *putchar_arg)
{
    UPYR_RETURN_IF_TRUE(!putchar_func, -1);  // TODO(Caleb): Return custom error code?

    s_putchar     = putchar_func;
    s_putchar_arg = putchar_arg;

    return 0;
}

void upyr_log_set_level(upyr_log_level_e level)
{
    s_level = UPYR_CLAMP(level, UPYR_LOG_LEVEL_DEBUG, UPYR_LOG_LEVEL_NOTIFICATION);
}

void upyr_log_set_validation_callback(upyr_log_validation_callback_f validation_callback_func)
{
    s_validation_callback = validation_callback_func;
}

void _upyr_log_generic(
    upyr_log_tag_t   tag,
    upyr_log_level_e level,
    const char      *file,
    int              line,
    const char      *color,
    const char      *prefix,
    const char      *postfix,
    const char      *format,
    ...)
{
    UPYR_RETURN_IF_TRUE(level < s_level);

    // TODO(Caleb): Add UPYR log tag validation
    const char *tag_str = "UNKNOWN";
    if (s_validation_callback)
    {
        tag_str = s_validation_callback(tag);
        UPYR_RETURN_IF_FALSE(tag_str);
    }

    _upyr_log_printf("%s%s [%s] ", color, prefix, tag_str);

    if (file)
    {
        _upyr_log_printf("%s:%d - ", basename(file), line);
    }

    va_list args;
    va_start(args, format);

    size_t size = (size_t)vsnprintf(NULL, 0, format, args) + 1;
    char   buffer[size];
    vsnprintf(buffer, size, format, args);

    va_end(args);

    buffer[size - 1] = '\0';
    _upyr_log_printf("%s%s%s", buffer, postfix, _UPYR_LOG_COLOR_DEFAULT);
}

void _upyr_log_hex_generic(
    upyr_log_tag_t   tag,
    upyr_log_level_e level,
    const char      *file,
    int              line,
    const char      *color,
    const char      *prefix,
    const void      *data,
    size_t           size,
    const char      *user_prefix)
{
    UPYR_RETURN_IF_FALSE(data && size);
    UPYR_RETURN_IF_TRUE(level < s_level);

    const char *tag_str = "UNKNOWN";
    if (s_validation_callback)
    {
        tag_str = s_validation_callback(tag);
        UPYR_RETURN_IF_FALSE(tag_str);
    }

    for (size_t line_start_byte_idx = 0; line_start_byte_idx < size; line_start_byte_idx += 16)
    {
        _upyr_log_printf("%s%s [%s] ", color, prefix, tag_str);

        if (file)
        {
            _upyr_log_printf("%s:%d - ", basename(file), line);
        }

        if (user_prefix)
        {
            _upyr_log_printf("%s - ", user_prefix);
        }

        _upyr_log_printf("%04zX: ", line_start_byte_idx);

        for (size_t i = 0; i < 16; ++i)
        {
            if (line_start_byte_idx + i < size)
            {
                _upyr_log_printf("%02X ", ((unsigned char *)data)[line_start_byte_idx + i]);
            }
            else
            {
                _upyr_log_printf("   ");
            }
        }

        _upyr_log_printf(" |");
        for (size_t i = 0; i < 16; ++i)
        {
            if (line_start_byte_idx + i < size)
            {
                char ch = ((char *)data)[line_start_byte_idx + i];
                _upyr_log_printf("%c", isprint((unsigned char)ch) ? ch : '.');
            }
            else
            {
                _upyr_log_printf(" ");
            }
        }
        _upyr_log_printf("|\n");
    }

    _upyr_log_puts(_UPYR_LOG_COLOR_DEFAULT);
}

static void _upyr_log_puts(const char *s)
{
    UPYR_RETURN_IF_FALSE(s && s_putchar);

    while (*s)
    {
        s_putchar(s_putchar_arg, *s, s[1] == '\0');
        s++;
    }
}

static void _upyr_log_printf(const char *format, ...)
{
    UPYR_RETURN_IF_FALSE(format);

    va_list args;
    va_start(args, format);

    size_t size = (size_t)vsnprintf(NULL, 0, format, args) + 1;
    char   buffer[size];
    vsnprintf(buffer, size, format, args);

    va_end(args);

    buffer[size - 1] = '\0';
    _upyr_log_puts(buffer);
}
