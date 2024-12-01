#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include "buffer.h"

typedef struct upyr_ringbuf_s
{
    buffer_t buffer;
    size_t   front_idx;
    size_t   back_idx;
    bool     is_full;
} upyr_ringbuf_t;

// clang-format off
#define _UPYR_RINGBUF_DECLARE(_name, _T, _size, _qualifiers)                                       \
    _qualifiers uint8_t   _##_name##_data[_size * sizeof(_T)] = {0};                               \
    _qualifiers upyr_ringbuf_t _name = {                                                           \
        .buffer =                                                                                  \
            {                                                                                      \
                .elem_size = sizeof(_T),                                                           \
                .num_elems = _size,                                                                \
                .data      = _##_name##_data,                                                      \
            },                                                                                     \
        .front_idx = 0,                                                                            \
        .back_idx  = 0,                                                                            \
        .is_full   = false,                                                                        \
    }
// clang-format on

/// @brief Declare a ring buffer.
/// @param _name The name of the ring buffer.
/// @param _T The type of the elements.
/// @param _size The size of the elements.
#define UPYR_RINGBUF_DECLARE(_name, _T, _size)   _UPYR_RINGBUF_DECLARE(_name, _T, _size, )

/// @brief Declare a static ring buffer.
/// @param _name The name of the ring buffer.
/// @param _T The type of the elements.
/// @param _size The size of the elements.
#define UPYR_RINGBUF_DECLARE_S(_name, _T, _size) _UPYR_RINGBUF_DECLARE(_name, _T, _size, static)

/// @brief Declare a volatile ring buffer.
/// @param _name The name of the ring buffer.
/// @param _T The type of the elements.
/// @param _size The size of the elements.
#define UPYR_RINGBUF_DECLARE_V(_name, _T, _size) _UPYR_RINGBUF_DECLARE(_name, _T, _size, volatile)

/// @brief Declare a static volatile ring buffer.
/// @param _name The name of the ring buffer.
/// @param _T The type of the elements.
/// @param _size The size of the elements.
#define UPYR_RINGBUF_DECLARE_SV(_name, _T, _size)                                                  \
    _UPYR_RINGBUF_DECLARE(_name, _T, _size, static volatile)

/// @brief Push data into the ring buffer.
/// @param rb The ring buffer to push data into.
/// @param data The data to push.
/// @param size The size of the data to push.
/// @return The number of bytes pushed, or -1 if the ring buffer is full.
ssize_t upyr_ringbuf_push(upyr_ringbuf_t *rb, void *data, size_t size);

/// @brief Pop data from the ring buffer.
/// @param rb The ring buffer to pop data from.
/// @param o_data The data to pop.
/// @param size The size of the data to pop.
/// @return The number of bytes popped, or -1 if the ring buffer is empty.
ssize_t upyr_ringbuf_pop(upyr_ringbuf_t *rb, void *o_data, size_t size);

/// @brief Get the size of the ring buffer.
/// @param rb The ring buffer to get the size of.
/// @return The size of the ring buffer.
size_t upyr_ringbuf_size(const upyr_ringbuf_t *rb);

/// @brief Get the capacity of the ring buffer.
/// @param rb The ring buffer to get the capacity of.
/// @return The capacity of the ring buffer.
size_t upyr_ringbuf_capacity(const upyr_ringbuf_t *rb);

/// @brief Check if the ring buffer is full.
/// @param rb The ring buffer to check.
/// @return True if the ring buffer is full, false otherwise.
bool upyr_ringbuf_is_full(const upyr_ringbuf_t *rb);

/// @brief Check if the ring buffer is empty.
/// @param rb The ring buffer to check.
/// @return True if the ring buffer is empty, false otherwise.
bool upyr_ringbuf_is_empty(const upyr_ringbuf_t *rb);

/// @brief Get the data of the ring buffer.
/// @param rb The ring buffer to get the data of.
/// @param o_size The size of the data.
/// @return The data of the ring buffer.
void *upyr_ringbuf_data(const upyr_ringbuf_t *rb, size_t *o_size);

/// @brief Peek at the data of the ring buffer.
/// @param rb The ring buffer to peek at.
/// @param i The index of the data to peek at.
/// @param o_size The size of the data.
/// @return The data of the ring buffer.
void *upyr_ringbuf_peek(const upyr_ringbuf_t *rb, size_t i, size_t *o_size);

/// @brief Peek at the front of the ring buffer.
/// @param rb The ring buffer to peek at.
/// @param o_size The size of the data.
/// @return The data of the ring buffer.
void *upyr_ringbuf_peek_front(const upyr_ringbuf_t *rb, size_t *o_size);

/// @brief Peek at the back of the ring buffer.
/// @param rb The ring buffer to peek at.
/// @param o_size The size of the data.
/// @return The data of the ring buffer.
void *upyr_ringbuf_peek_back(const upyr_ringbuf_t *rb, size_t *o_size);

/// @brief Clear the ring buffer.
/// @param rb The ring buffer to clear.
void upyr_ringbuf_clear(upyr_ringbuf_t *rb);

#endif  // __RING_BUFFER_H__
