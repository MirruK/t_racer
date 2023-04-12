all: game

%.o: %.c
	echo "Compiling sources"
	cc -g -c *.c 

game: fetch_text.o game.o text_helpers.o
	echo "Linking files"
	echo "Creating executable"
	cc -g -o game fetch_text.o game.o text_helpers.o -lncurses

clean:
	echo "Cleaning up old .o files"
	rm *.o || echo No object files
	rm game
