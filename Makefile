all :
	gcc *.c -o out `pkg-config --cflags --libs sdl2` -lSDL2_image
