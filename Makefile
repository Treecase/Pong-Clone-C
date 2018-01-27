BALL=src/ball.c src/ball.h
BUMPER=src/bumper.c src/bumper.h
UTIL=src/util.c src/util.h
OBJ=src/obj/ball.o src/obj/bumper.o src/obj/util.o

pong : src/main.c src/consts.h $(OBJ)
	gcc src/main.c $(OBJ) -o pong -lSDL2 -lSDL2_image

src/obj/ball.o : $(BALL) $(BUMPER) src/consts.h
	gcc src/ball.c -c -o src/obj/ball.o -lSDL2 -lSDL2_image

src/obj/bumper.o : $(BALL) $(BUMPER) src/consts.h
	gcc src/bumper.c -c -o src/obj/bumper.o -lSDL2 -lSDL2_image

src/obj/util.o : $(UTIL) src/consts.h
	gcc src/util.c -c -o src/obj/util.o -lSDL2 -lSDL2_image

clean :
	rm $(OBJ) pong
