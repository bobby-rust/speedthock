CC = clang
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -luser32

SRC = main.c
RES = example.res
OUT = main.exe

build: $(OUT)

$(OUT): $(SRC) $(RES)
	$(CC) $(CFLAGS) -o main.exe main.c $(LDFLAGS)

clean:
	del $(OUT)

.PHONY: all clean
