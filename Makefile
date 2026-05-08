CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c src/parser.c src/executor.c src/builtins.c

OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(TARGET)
