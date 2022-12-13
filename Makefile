all: nqueens knights taquin board_queens.o board_knight.o board_taquin.o list.o

list.o: list.c list.h
	gcc -c list.c

board_queens.o: board_queens.c board.h
	gcc -c board_queens.c

board_knight.o: board_knight.c board.h
	gcc -c board_knight.c

board_taquin.o: board_taquin.c board.h
	gcc -c board_taquin.c

nqueens: nqueens.c board_queens.c list.c board.h list.h item.h
	gcc -o nqueens nqueens.c board_queens.c list.c

knights: knights.c board_knight.c list.c board.h list.h item.h
	gcc -o knights knights.c board_knight.c list.c

taquin: taquin.c board_taquin.c list.c board.h list.h item.h
	gcc -o taquin taquin.c board_taquin.c list.c

clean: 
	rm *.o nqueens knights taquin


