all:
	gcc -o out/main src/main.c src/entrance.c src/file/file.c src/render/shader.c src/iocon/input.c -lGLEW -lGL -lX11

