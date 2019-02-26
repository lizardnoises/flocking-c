src = $(wildcard *.c)
obj = $(src:.c=.o)

CC = gcc
CFLAGS = -std=c99 -Iraylib/src
LDFLAGS = -Lraylib/mingw/i686-w64-mingw32/lib -lraylib -lopengl32 -lgdi32 -lm

.PHONY: clean raylib

boids: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
ifeq ($(OS), Windows_NT)
	del $(obj) boids.exe
else
	rm -f $(obj) boids
endif

raylib:
	$(MAKE) -C raylib/src PLATFORM=PLATFORM_DESKTOP