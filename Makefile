
FILE=main.c
BIN=app

all: build run clean

build:
	gcc -openmp $(FILE) -o $(BIN)

run:
	./$(BIN)

clean:
	rm $(BIN)