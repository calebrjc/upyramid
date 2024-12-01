#include "upyramid/dsa/ring_buffer.h"

#include "upyramid/assert.h"

size_t upyr_ringbuf_size(const upyr_ringbuf_t *rb)
{
    UPYR_RETURN_IF_FALSE(rb, 0);

    if (upyr_ringbuf_is_full(rb))
    {
        return upyr_ringbuf_capacity(rb);
    }

    if (rb->back_idx >= rb->front_idx)
    {
        return rb->back_idx - rb->front_idx;
    }

    return upyr_ringbuf_capacity(rb) - rb->front_idx + rb->back_idx;
}

size_t upyr_ringbuf_capacity(const upyr_ringbuf_t *rb)
{
    UPYR_RETURN_IF_FALSE(rb, 0);

    return upyr_buffer_size(&rb->buffer);
}

bool upyr_ringbuf_is_full(const upyr_ringbuf_t *rb)
{
    UPYR_RETURN_IF_FALSE(rb, false);

    return rb->is_full;
}

bool upyr_ringbuf_is_empty(const upyr_ringbuf_t *rb)
{
    UPYR_RETURN_IF_FALSE(rb, true);

    return (rb->back_idx == rb->front_idx) && !upyr_ringbuf_is_full(rb);
}

ssize_t upyr_ringbuf_push(upyr_ringbuf_t *rb, void *data, size_t size)
{
    UPYR_RETURN_IF_FALSE(rb && data && !upyr_ringbuf_is_full(rb), -1);

    ssize_t bytes_written = upyr_buffer_write(&rb->buffer, rb->back_idx, data, size);
    UPYR_RETURN_IF_TRUE(bytes_written < 0, -1);

    size_t next_idx = rb->back_idx + 1;
    rb->back_idx    = (next_idx < upyr_buffer_size(&rb->buffer)) ? next_idx : 0;

    if (rb->back_idx == rb->front_idx)
    {
        rb->is_full = true;
    }

    return bytes_written;
}

ssize_t upyr_ringbuf_pop(upyr_ringbuf_t *rb, void *o_data, size_t size)
{
    UPYR_RETURN_IF_FALSE(rb && o_data && !upyr_ringbuf_is_empty(rb), -1);

    ssize_t bytes_written = upyr_buffer_read(&rb->buffer, rb->front_idx, o_data, size);
    UPYR_RETURN_IF_TRUE(bytes_written < 0, -1);

    size_t next_idx = rb->front_idx + 1;
    rb->front_idx   = (next_idx < upyr_buffer_size(&rb->buffer)) ? next_idx : 0;

    if (rb->back_idx != rb->front_idx)
    {
        rb->is_full = false;
    }

    return bytes_written;
}

void *upyr_ringbuf_peek_front(const upyr_ringbuf_t *rb, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(rb, NULL);

    return upyr_buffer_peek(&rb->buffer, rb->front_idx, o_size);
}

void *upyr_ringbuf_peek_back(const upyr_ringbuf_t *rb, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(rb, NULL);

    return upyr_buffer_peek(
        &rb->buffer,
        (rb->back_idx == 0) ? upyr_buffer_size(&rb->buffer) - 1 : rb->back_idx - 1,
        o_size);
}

void *upyr_ringbuf_peek(const upyr_ringbuf_t *rb, size_t i, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(rb && i < upyr_ringbuf_size(rb), NULL);

    return upyr_buffer_peek(&rb->buffer, (rb->front_idx + i) % upyr_ringbuf_capacity(rb), o_size);
}

void *upyr_ringbuf_data(const upyr_ringbuf_t *rb, size_t *o_size)
{
    UPYR_RETURN_IF_FALSE(rb, NULL);

    return upyr_buffer_data(&rb->buffer, o_size);
}

void upyr_ringbuf_clear(upyr_ringbuf_t *rb)
{
    UPYR_RETURN_IF_FALSE(rb);

    upyr_buffer_clear(&rb->buffer);

    rb->is_full  = false;
    rb->back_idx = rb->front_idx = 0;
}
