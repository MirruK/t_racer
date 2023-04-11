all: game

*.o: fetch_text.c game.c text_helpers.c
	echo "Compiling sources"
	cc -g -c *.c 

game: fetch_text.o game.o text_helpers.o
	echo "Linking files"
	echo "Creating executable"
	cc -O0 -lcurses -g -o game fetch_text.o game.o text_helpers.o 

clean:
	echo "Cleaning up old .o files"
	rm *.o
