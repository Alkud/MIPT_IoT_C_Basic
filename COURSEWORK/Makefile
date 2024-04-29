C       := gcc
C_FLAGS := -std=c99 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

EXECUTABLE  := temp_stat_cli


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c main.c
	$(C) $(C_FLAGS) -I $(INCLUDE) $^ -o $@

clean:
	-rm $(BIN)/*
