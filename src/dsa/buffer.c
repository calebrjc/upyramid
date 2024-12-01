#include "upyramid/dsa/buffer.h"

#include <string.h>

#include "upyramid/assert.h"
#include "upyramid/math.h"

#define BUFFER_GET_ELEM(_buffer, _i) (&_buffer->data[_i * _buffer->elem_size])

ssize_t upyr_buffer_read(const buffer_t *buffer, size_t i, void *o_data, size_t size)
{
    UPYR_RETURN_IF_FALSE(buffer && o_data && i < buffer->num_elems, -1);

    ssize_t copy_size = UPYR_MIN(size, buffer->elem_size);
    memcpy(o_data, BUFFER_GET_ELEM(buffer, i), (size_t)copy_size);

    return copy_size;
}

ssize_t upyr_buffer_write(buffer_t *buffer, size_t i, const void *data, size_t size)
{
    UPYR_RETURN_IF_FALSE(buffer && data && i < buffer->num_elems, -1);

    ssize_t copy_size = UPYR_MIN(size, buffer->elem_size);
    memcpy(BUFFER_GET_ELEM(buffer, i), data, (size_t)copy_size);

    return copy_size;
}

size_t upyr_buffer_size(const buffer_t *buffer)
{
    UPYR_RETURN_IF_FALSE(buffer, 0);

    return buffer->num_elems;
}

void *upyr_buffer_data(const buffer_t *buffer, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(buffer, NULL);

    if (o_size)
    {
        *o_size = buffer->elem_size * buffer->num_elems;
    }

    return BUFFER_GET_ELEM(buffer, 0);
}

void *upyr_buffer_peek(const buffer_t *buffer, size_t i, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(buffer && i < buffer->num_elems, NULL);

    if (o_size)
    {
        *o_size = buffer->elem_size;
    }

    return BUFFER_GET_ELEM(buffer, i);
}

void upyr_buffer_clear(buffer_t *buffer)
{
    UPYR_RETURN_IF_FALSE(buffer);

    memset(buffer->data, 0, buffer->num_elems * buffer->elem_size);
}
