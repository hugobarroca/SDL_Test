CC=gcc
OUT_DIR=bin

all: $(OUT_DIR)/main

$(OUT_DIR):
	mkdir -p bin

$(OUT_DIR)/main: main.c $(OUT_DIR)
	$(CC) -o $(OUT_DIR)/main main.c -lSDL2 -lSDL2_ttf

.PHONY: clean
clean:
	rm -rf bin
