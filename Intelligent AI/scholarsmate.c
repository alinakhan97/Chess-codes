

/********************************************************************
 *                          scholarsmate.c                          *
 *                 scholar's mate to test chesslib                  *
 *                                                                  *
 *               (C)2015 <georgekoskerid@outlook.com>               *
 *                                                                  *
 ********************************************************************/

#include "chesslib.h"
#include "chesslib-cli.h"


int main(void)
{
	ch_template chess_board[8][8];
	int round = WHITE;
	clock_t start, stop;
	double total_cpu_time;
	KingState BlackKing, WhiteKing;

	start = clock();

	initChessboard(chess_board);
	playMoves(chess_board, &round, 7, "e2e4", "e7e5", "f1c4", "g8f6", "d1h5", "b8c6", "h5f7");
	getAllMoves(chess_board, round);

	stop = clock();
	total_cpu_time = ((double)(stop - start))/CLOCKS_PER_SEC;
	printf("CPU TIME ELAPSED:%lf\n\n", total_cpu_time);
	printBoard(chess_board, 'l');
	printf("\t\t\t***WHITE MOVES***\n");
	printWhiteMoves();
	printf("\t\t\t***BLACK MOVES***\n");
	printBlackMoves();

	if (BlackKing == checkmate)
		printf("White wins!\n");
	if (WhiteKing == checkmate)
		printf("Black wins!\n");
	return 0;
}

