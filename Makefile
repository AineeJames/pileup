CC = gcc
CFLAGS = -O3 -g3
SRC := src
OBJ := obj
SOURCES := $(wildcard $(SRC)/*.c)
HEADERS := $(wildcard $(SRC)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

pileup: $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ) pileup
