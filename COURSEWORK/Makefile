C       := g++
C_FLAGS := -std=c99 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
    clear
    ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
    $(C) $(C_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
    -rm $(BIN)/*
