test: main
	./main

main: main.c engine.c list_funcs.c
	gcc -g -pthread main.c engine.c list_funcs.c -o $@
