set(UPYR_SRCS src/cli.c src/log.c)

idf_component_register(SRCS ${UPYR_SRCS} INCLUDE_DIRS "include")
