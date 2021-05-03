test: main
	./main

main: main.c engine.c list_funcs.c
	gcc $? -o main
