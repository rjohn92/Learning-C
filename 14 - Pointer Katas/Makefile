CC      := cc
CFLAGS  := -std=c17 -g -O0 -Wall -Wextra -Wpedantic \
           -fsanitize=address,undefined -fno-omit-frame-pointer
INC     := -Iinclude
SRC     := src/my_string.c tests/test_my_string.c
BIN     := build/tests

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BIN)

clean:
	rm -rf build

.PHONY: all clean
