connectn.out : main.o setup_game.o play_game.o
	gcc main.o setup_game.o play_game.o -o connectn.out

main.o : main.c setup_game.h play_game.h
	gcc -g -Wall -c main.c

setup_game.o : setup_game.c setup_game.h
	gcc -g -Wall -c setup_game.c

play_game.o : play_game.c play_game.h setup_game.h
	gcc -g -Wall -c play_game.c

clean :
	rm *.o connectn.out