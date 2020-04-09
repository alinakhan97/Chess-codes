/********************************************************************
 *                          chessgame-cli.c                         *
 *       small game making use of the chesslib.c chess library      *
 *                                                                  *
 *              (C)2015 <georgekoskerid@outlook.com>                *
 *                                                                  *
 ********************************************************************/

#include "chesslib.h"
#include "chesslib-cli.h"

#define TEST_ROUNDS 3


int main(void)
{
	ch_template chess_board[8][8];
	char *playerInput = NULL, start_move[3], end_move[3];
	initChessboard(chess_board);
	int round = WHITE, total_rounds = 1;
	bool pr_moves = false;
	char *test_moves[] = {"h2h4", "b7b5", "h4h5"};
	KingState BlackKing,WhiteKing;

	start_move[2] = '\0';
	end_move[2] = '\0';
	for (;;) {
		deleteMoves();
		getAllMoves(chess_board, round);
		if (BlackKing == checkmate || WhiteKing == checkmate)
			break;
		if (total_rounds > TEST_ROUNDS) {
			clear_screen();
			//printBoard(chess_board, 'l');
			if (pr_moves) {
				printf("\t\t\t***WHITE MOVES***\n");
				printWhiteMoves();
				printf("\t\t\t***BLACK MOVES***\n");
				printBlackMoves();
				pr_moves = false;
			}
			if (round == WHITE)
				printf("White plays: ");
			else
				printf("Black plays: ");
			playerInput = getPlayerInput();
			if (!playerInput)
				continue;
			if (strlen(playerInput) == 4) {
				if (!strncmp(playerInput, "quit", 4) || !strncmp(playerInput, "exit", 4)) {
					free(playerInput);
					playerInput = NULL;
					deleteMoves();
					return 0;
				}
			} else if (strlen(playerInput) == 1) {
				pr_moves = true;
				free(playerInput);
				playerInput = NULL;
				continue;
			} else {
				free(playerInput);
				playerInput = NULL;
				continue;
			}
			start_move[0] = playerInput[0];
			start_move[1] = playerInput[1];
			end_move[0] = playerInput[2];
			end_move[1] = playerInput[3];
		} else {
			//printBoard(chess_board, 'l');
			start_move[0] = test_moves[total_rounds-1][0];
			start_move[1] = test_moves[total_rounds-1][1];
			end_move[0] = test_moves[total_rounds-1][2];
			end_move[1] = test_moves[total_rounds-1][3];
		}
		if (makeMove(chess_board, start_move, end_move, round)) {
			round = (round == BLACK)?WHITE:BLACK;
			total_rounds++;
		}
		free(playerInput);
		playerInput = NULL;
	}
	clear_screen();
	//printBoard(chess_board, 'l');
	pr_moves = false;
	if (BlackKing == checkmate)
		printf("White wins!\n");
	if (WhiteKing == checkmate)
		printf("Black wins!\n");
	return 0;
}

