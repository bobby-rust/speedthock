#CC = clang
#CFLAGS = -Wall -Wextra -std=c11
#LDFLAGS = -luser32
#MT = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\mt.exe"  # Adjust the path to mt.exe
#SRC = main.c
#RES = your_icon.res
#OUT = speedthock.exe
#MANIFEST = speedthock.exe.manifest
#VERSION = v0.1
#DEST_FOLDER = "build/SpeedThock $(VERSION)"
#PRODDEST = $(DEST_FOLDER)/speedthock.exe

#build: $(OUT)
#prod: $(PRODDEST)

#$(OUT): $(SRC) $(RES)
	# $(CC) $(CFLAGS) -o $(OUT) $(SRC) $(RES) $(LDFLAGS)

#$(PRODDEST): $(OUT)
#	@echo "Running commands in $(ComSpec)"
#	@if not exist $(DEST_FOLDER) mkdir $(DEST_FOLDER)
#	copy $(OUT) $(PRODDEST) 
#	$(MT) -manifest $(MANIFEST) -outputresource:$(PRODDEST);1

#clean:
# 	del $(OUT)
# 	rmdir build -Recurse -Force

# .PHONY: build clean

CC=clang
CFLAGS=-Wall -Wextra
LDFLAGS=-luser32
VERSION=v0.1.1
PRODDEST="build\SpeedThock $(VERSION)"
MT = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\mt.exe" # Adjust the path to mt.exe
MANIFEST = speedthock.exe.manifest

# Target for development build
dev: main.c
	$(CC) $(CFLAGS) $^ -o SpeedThock_dev.exe $(LDFLAGS)

# Target for production build
prod: main.c
	@if not exist $(PRODDEST) mkdir $(PRODDEST) 
	$(CC) $(CFLAGS) -O3 $^ -o $(PRODDEST)\SpeedThock.exe $(LDFLAGS)
	@if not exist $(PRODDEST)\sounds mkdir $(PRODDEST)\sounds
	xcopy /s sounds $(PRODDEST)\sounds 
	$(MT) -manifest $(MANIFEST) -outputresource:$(PRODDEST)\SpeedThock.exe;1

# Target to clean all builds
clean:
	del SpeedThock_dev.exe

# Target to clean only the production build
clean_prod:
	rmdir /s /q build
