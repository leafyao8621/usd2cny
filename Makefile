CC = gcc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
COMP = $(shell curl-config --cflags)
LINK = $(shell curl-config --libs)
BIN = usd2cny

%.o: %.c
	$(CC) -c $< -o $@ $(COMP)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LINK)

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)