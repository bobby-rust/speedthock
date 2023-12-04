CC = clang
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -luser32

SRC = main.c
RES = example.res
OUT = main.exe

all: $(OUT)

$(OUT): $(SRC) $(RES)
  $(CC) $(CFLAGS) -o $(LDFLAGS)

clean:
  del $(OUT)

.PHONY: all clean
