set(UPYR_SRCS src/cli.c src/log.c src/dsa/buffer.c src/dsa/ring_buffer.c)

idf_component_register(SRCS ${UPYR_SRCS} INCLUDE_DIRS "include")
