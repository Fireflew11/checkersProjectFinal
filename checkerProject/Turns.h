#ifndef __TURNS_H
#define __TURNS_H
#include "MultipleSourceMoves.h"
#define AMOUNT_OF_PIECES_IN_START 12
typedef struct _Statistics {
	int maxCaps;
	int bMoves;
	int tMoves;
	int curTPiecesAmount;
	int curBPiecesAmount;
	Player winner;
	Player maxCapsPlayer;
}statistics;
void Turn(Board board, Player player);
void updateBoardWithMove(Board board, Player player, SingleSourceMovesList* movesList);
int getSideFlag(int side);
void PlayGame(Board board, Player starting_player);
void updateStatistics(statistics* stats, int curBAmountCounter, int curTAmountCounter);
void updateCurMove(Board board, Player player, checkersPos* curPos, checkersPos* newPos, int typeFlag, int sideFlag);
#endif