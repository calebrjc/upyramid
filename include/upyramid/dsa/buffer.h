#ifndef __UPYR_DSA_BUFFER_H__
#define __UPYR_DSA_BUFFER_H__

#include <stdio.h>

#include "upyramid/detail/common.h"

typedef struct
{
    size_t   elem_size;
    size_t   num_elems;
    uint8_t *data;
} buffer_t;

// clang-format off
#define _UPYR_BUFFER_DECLARE(_name, _T, _size, _qualifiers)                                        \
    _qualifiers uint8_t  _##_name##_data[_size * sizeof(_T)] = {0};                                \
    _qualifiers buffer_t _name = {                                                                 \
        .elem_size = sizeof(_T),                                                                   \
        .num_elems = _size,                                                                        \
        .data      = _##_name##_data,                                                              \
    }
// clang-format on

/// @brief Declare a buffer.
/// @param _name The name of the buffer.
/// @param _T The type of the elements.
/// @param _size The number of elements.
#define UPYR_BUFFER_DECLARE(_name, _T, _size)   _UPYR_BUFFER_DECLARE(_name, _T, _size, )

/// @brief Declare a static buffer.
/// @param _name The name of the buffer.
/// @param _T The type of the elements.
/// @param _size The number of elements.
#define UPYR_BUFFER_DECLARE_S(_name, _T, _size) _UPYR_BUFFER_DECLARE(_name, _T, _size, static)

/// @brief Declare a volatile buffer.
/// @param _name The name of the buffer.
/// @param _T The type of the elements.
/// @param _size The number of elements.
#define UPYR_BUFFER_DECLARE_V(_name, _T, _size) _UPYR_BUFFER_DECLARE(_name, _T, _size, volatile)

/// @brief Declare a static volatile buffer.
/// @param _name The name of the buffer.
/// @param _T The type of the elements.
/// @param _size The number of elements.
#define UPYR_BUFFER_DECLARE_SV(_name, _T, _size)                                                   \
    _UPYR_BUFFER_DECLARE(_name, _T, _size, static volatile)

/// @brief Read data from the buffer.
/// @param buffer The buffer to read from.
/// @param i The index to read from.
/// @param o_data The data buffer to read into.
/// @param size The size of the data buffer to read into.
/// @return The number of bytes read, or -1 if the read failed.
ssize_t upyr_buffer_read(const buffer_t *buffer, size_t i, void *o_data, size_t size);

/// @brief Write data to the buffer.
/// @param buffer The buffer to write to.
/// @param i The index to write to.
/// @param data The data to write.
/// @param size The size of the data to write.
/// @return The number of bytes written, or -1 if the write failed.
ssize_t upyr_buffer_write(buffer_t *buffer, size_t i, const void *data, size_t size);

/// @brief Return the size of the buffer.
/// @param buffer The buffer to get the size of.
/// @return The size of the buffer.
size_t upyr_buffer_size(const buffer_t *buffer);

/// @brief Get the underlying data of the buffer.
/// @param buffer The buffer to get the data of.
/// @param o_size [Optional] The size of the data pointed to.
/// @return A pointer to the data of the buffer, or NULL if invalid arguments were passed.
void *upyr_buffer_data(const buffer_t *buffer, size_t *o_size);

/// @brief Peek at the data in the buffer.
/// @param buffer The buffer to peek into.
/// @param i The index to peek into.
/// @param o_size [Optional] The size of the data pointed to.
/// @return A pointer to the data at the index, or NULL if the index is out of bounds.
void *upyr_buffer_peek(const buffer_t *buffer, size_t i, size_t *o_size);

/// @brief Clear the buffer.
/// @param buffer The buffer to clear.
void upyr_buffer_clear(buffer_t *buffer);

#endif  // __UPYR_DSA_BUFFER_H__
