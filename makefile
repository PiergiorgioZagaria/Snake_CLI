test: main
	./main

main: main.o engine.o list_funcs.o game.o
	gcc -g -pthread -o $@ main.o engine.o list_funcs.o game.o 

main.o: main.c game.h
	gcc -c $?

engine.o: engine.c engine.h list_funcs.h
	gcc -c $?

list_funcs.o: list_funcs.h

game.o: game.c game.h engine.h list_funcs.h
	gcc -c $?

clean:
	rm *.o *.gch
