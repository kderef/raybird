CC = gcc
CFLAGS = -Iraylib/src -Iincbin/ -Lraylib/src -lraylib
CFLAGS_REL = --static -Os -s -ffast-math -Wall -Wextra

ifeq ($(OS), Windows_NT)
	CFLAGS += -lwinmm -lgdi32 -lopengl32
	CFLAGS_REL += -mwindows
endif

all: debug

debug: raylib/src/libraylib.a
	$(CC) src/main.c -o bin/RayBird -DDEBUG=1 $(CFLAGS)


release: raylib/src/libraylib.a
	$(CC) src/main.c -o bin/RayBird -DDEBUG=0 $(CFLAGS) $(CFLAGS_REL)

run:
	./bin/RayBird