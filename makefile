CC=gcc
name=play
lib=pthread
main:	clean
	$(CC) -o $(name) $(name).c -Wall -$(lib)

clean :
	rm -f $(name) *.o

