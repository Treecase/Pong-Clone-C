# TODO clean this up

BALL=src/ball.c src/ball.h
BUMPER=src/bumper.c src/bumper.h
UTIL=src/util.c src/util.h
GRAPHICS=src/graphics.c src/graphics.h
OBJ=src/obj/ball.o src/obj/bumper.o src/obj/util.o src/obj/graphics.o

pong : src/main.c src/consts.h $(OBJ)
	gcc src/main.c $(OBJ) -o pong -lSDL2 -lSDL2_image -Wall

src/obj/ball.o : $(BALL) $(BUMPER) src/consts.h
	gcc src/ball.c -c -o src/obj/ball.o

src/obj/bumper.o : $(BALL) $(BUMPER) src/consts.h
	gcc src/bumper.c -c -o src/obj/bumper.o

src/obj/util.o : $(UTIL) src/consts.h
	gcc src/util.c -c -o src/obj/util.o

src/obj/graphics.o : $(GRAPHICS) src/consts.h
	gcc src/graphics.c -c -o src/obj/graphics.o -lSDL2 -lSDL2_image

clean :
	rm $(OBJ) pong
