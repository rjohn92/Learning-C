CC      := gcc
CFLAGS  := -std=c17 -Wall -Wextra -Wpedantic -O0 -g

SRC     := $(wildcard src/*.c)

numstats: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@