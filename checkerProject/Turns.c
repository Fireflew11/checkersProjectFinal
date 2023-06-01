#include "Turns.h"
#include "BoardFunctions.h"
#define RIGHT 1
#define LEFT -1

void Turn(Board board, Player player) {
	MultipleSourceMovesList* multiList = FindAllPossiblePlayerMoves(board, player);
	MultipleSourceMovesListCell* bestCell = multiList->head, * curCell = multiList->head->next;
	while (curCell != NULL) {
		if (curCell->single_source_moves_list->tail->captures > bestCell->single_source_moves_list->tail->captures)
			bestCell = curCell;
		else if (curCell->single_source_moves_list->tail->captures == bestCell->single_source_moves_list->tail->captures) {
			if (player == PLAYER_T && curCell->single_source_moves_list->head->position->row > bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == PLAYER_T && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == PLAYER_T && curCell->single_source_moves_list->head->position->col > bestCell->single_source_moves_list->head->position->col)
				bestCell = curCell;
			else if (player == PLAYER_B && curCell->single_source_moves_list->head->position->row < bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == PLAYER_B && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == PLAYER_B && curCell->single_source_moves_list->head->position->col < bestCell->single_source_moves_list->head->position->col)
				bestCell = curCell;
		}
		curCell = curCell->next;
	}
	printf("%c's turn:\n", player);
	printList(bestCell->single_source_moves_list);
	updateBoardWithMove(board, player, bestCell->single_source_moves_list);
	freeMultiList(multiList);
}

void updateCurMove(Board board, Player player, checkersPos* curPos, checkersPos* newPos, int typeFlag, int sideFlag) {
	board[newPos->row - 'A'][newPos->col - '1'] = player;
	board[curPos->row - 'A'][curPos->col - '1'] = ' ';
	if (abs(newPos->col - curPos->col) == 2)
		board[curPos->row + typeFlag - 'A'][curPos->col + sideFlag - '1'] = ' ';

}
int getSideFlag(int side) {
	if (side > 0)
		return RIGHT;
	else
		return LEFT;
}

//list size is at least 2 (minimum of head currentPostion and tail the wanted move)
void updateBoardWithMove(Board board, Player player, SingleSourceMovesList* movesList) {
	SingleSourceMovesListCell* curCell = movesList->head;
	//assume curCell not NULL because we called this function means there is a turn to be played
	while (curCell->next != NULL) {
		checkersPos* curPos = curCell->position;
		//next is not NULL
		curCell = curCell->next;
		checkersPos* newPos = curCell->position;
		int typeFlag = getFlagType(player);
		int sideFlag = getSideFlag(newPos->col - curPos->col);
		updateCurMove(board, player, curPos, newPos, typeFlag, sideFlag);
	}
}

void updateStatistics(statistics * stats, int curBAmountCounter, int curTAmountCounter) {
	int curMaxB = stats->curBPiecesAmount - curBAmountCounter;
	int curMaxT = stats->curTPiecesAmount - curTAmountCounter;
	if (stats->maxCaps < curMaxB)
	{
		stats->maxCaps = curMaxB;
		stats->maxCapsPlayer = PLAYER_B;
	}
	else if (stats->maxCaps < curMaxT) {
		stats->maxCaps = curMaxT;
		stats->maxCapsPlayer = PLAYER_T;
	}
	stats->curBPiecesAmount = curBAmountCounter;
	stats->curTPiecesAmount = curTAmountCounter;
}

void PlayGame(Board board, Player starting_player) {
	statistics stats;
	stats.bMoves = stats.maxCaps = stats.tMoves = 0;
	stats.curBPiecesAmount = stats.curTPiecesAmount = AMOUNT_OF_PIECES_IN_START;
	int curBAmountCounter = 0, curTAmountCounter = 0;
	bool gameOver = false;
	Player curPlayer = starting_player;
	drawBoard(board);
	while (!gameOver) {
		Turn(board, curPlayer);
		if (curPlayer == PLAYER_T)
			stats.tMoves++;
		else
			stats.bMoves++;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == PLAYER_B)
					curBAmountCounter++;
				else if (board[i][j] == PLAYER_T)
					curTAmountCounter++;
			}
			
			if (board[0][i] == PLAYER_B)
			{
				gameOver = true;
				stats.winner = PLAYER_B;
			}
			else if (board[7][i] == PLAYER_T) {
				gameOver = true;
				stats.winner = PLAYER_T;
			}
		}
		updateStatistics(&stats, curBAmountCounter, curTAmountCounter);
		curBAmountCounter = curTAmountCounter = 0;
		if (stats.curBPiecesAmount == 0)
		{
			gameOver = true;
			stats.winner = PLAYER_T;
		}
		else if (stats.curTPiecesAmount == 0)
		{
			gameOver = true;
			stats.winner = PLAYER_B;
		}
		
		curPlayer = getOtherType(curPlayer);
		drawBoard(board);
		printf("\n\n");
	}
	printf(".\n.\n.\n");
	printf("%c wins!\n", stats.winner);
	if (stats.winner == PLAYER_T)
		printf("%c performed %d moves.\n", stats.winner, stats.tMoves);
	else
		printf("%c performed %d moves.\n", stats.winner, stats.bMoves);
	printf("%c performed the highest number of captures in a single move - %d", stats.maxCapsPlayer, stats.maxCaps);
}