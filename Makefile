all: nqueens knights board_queens.o board_knight.o list.o

list.o: list.c list.h
	gcc -c list.c

board_queens.o: board_queens.c board.h
	gcc -c board_queens.c

board_knight.o: board_knight.c board.h
	gcc -c board_knight.c

nqueens: nqueens.c board_queens.c list.c board.h list.h item.h
	gcc -o nqueens nqueens.c board_queens.c list.c

knights: knights.c board_knight.c list.c board.h list.h item.h
	gcc -o knights knights.c board_knight.c list.c

clean: 
	rm *.o nqueens knights


