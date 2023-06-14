jogo: jogo.o main.o maps.o maps.o enemy.o bullet.o
	gcc jogo.o main.o maps.o enemy.o bullet.o -o jogo -lraylib
main.o: main.c
	gcc -c main.c 
jogo.o: jogo.c jogo.h 
	gcc -c jogo.c 
maps.o: maps.c jogo.h 
	gcc -c maps.c jogo.h 
enemy.o: enemy.c jogo.h
	gcc -c enemy.c jogo.h
bullet.o: bullet.c jogo.h
	gcc -c bullet.c jogo.h