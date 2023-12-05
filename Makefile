
CC = clang
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -luser32
MT = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\mt.exe"  # Adjust the path to mt.exe

SRC = main.c
RES = your_icon.res
OUT = speedthock.exe
MANIFEST = speedthock.exe.manifest
VERSION = v0.1
DEST_FOLDER = "build/SpeedThock $(VERSION)"
PRODDEST = $(DEST_FOLDER)/speedthock.exe

build: $(OUT)
prod: $(PRODDEST)

$(OUT): $(SRC) $(RES)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(RES) $(LDFLAGS)

$(PRODDEST): $(SRC) $(RES)
	@if not exist $(DEST_FOLDER) mkdir $(DEST_FOLDER)
	$(CC) $(CFLAGS) -o $(PRODDEST) $(SRC) $(RES) $(LDFLAGS)
	$(MT) -manifest $(MANIFEST) -outputresource:$(PRODDEST);1

clean:
	del $(OUT)
	del $(PRODDEST)

.PHONY: build clean
