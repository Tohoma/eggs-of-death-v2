CC = gcc

SRCS = eggs-of-death.c
EXEC = eggs-of-death

SDL_LIB_DIR = ../lib/SDL3-3.2.28/x86_64-w64-mingw32

LIB_NAME = SDL3

INCLUDE_DIR = $(SDL_LIB_DIR)/include/

CFLAGS = -I$(INCLUDE_DIR)
LDFLAGS = -L$(SDL_LIB_DIR)/lib/

LIBS = -lSDL3 -mwindows

move_sdl3_dll:
	cp $(SDL_LIB_DIR)/bin/SDL3.dll .

all: $(EXEC)

$(EXEC): move_sdl3_dll
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(EXEC) *.o
