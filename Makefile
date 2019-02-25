all:
	gcc -std=c99 -o main main.c v2.c boids.c -Iraylib\src -Lraylib\mingw\i686-w64-mingw32\lib -lraylib -lopengl32 -lgdi32