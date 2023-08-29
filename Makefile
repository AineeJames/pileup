CC = gcc
CFLAGS = -O3 -g3 -lm
SRC := src
OBJ := obj
SOURCES := $(wildcard $(SRC)/*.c)
HEADERS := $(wildcard $(SRC)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
LFLAGS := $(shell pkg-config raylib --libs)
CFLAGS += $(shell pkg-config raylib --cflags)

pileup: $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	@mkdir -p $(OBJ)
	$(CC) $(LFLAGS) -I$(SRC) -c $< -o $@ $(CFLAGS) 

.PHONY: clean

clean:
	rm -rf $(OBJ) pileup
