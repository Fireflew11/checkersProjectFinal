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
			if (player == 'T' && curCell->single_source_moves_list->head->position->row > bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == 'T' && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == 'T' && curCell->single_source_moves_list->head->next->position->col > bestCell->single_source_moves_list->head->next->position->col)
				bestCell = curCell;
			else if (player == 'B' && curCell->single_source_moves_list->head->position->row < bestCell->single_source_moves_list->head->position->row)
				bestCell = curCell;
			else if (player == 'B' && curCell->single_source_moves_list->head->position->row == bestCell->single_source_moves_list->head->position->row &&
				player == 'B' && curCell->single_source_moves_list->head->next->position->col < bestCell->single_source_moves_list->head->next->position->col)
				bestCell = curCell;
		}
		curCell = curCell->next;
	}
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

void PlayGame(Board board, Player starting_player) {
	bool gameOver = false;
	Player curPlayer = starting_player;
	while (!gameOver) {
		Turn(board, curPlayer);
		for (int i = 0; i < 8; i++)
		{
			if (board[0][i] == 'B' || board[7][i] == 'T')
			{
				gameOver = true;
				i = 8;
			}
		}
		curPlayer = getOtherType(curPlayer);
		drawBoard(board);
		printf("\n\n");
	}
}