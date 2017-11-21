all: pipeit.c
	gcc -o test pipeit.c
clean:
	rm *.o
run: all
	./test
