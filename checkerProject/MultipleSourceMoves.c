#include "MultipleSourceMoves.h"

//This function checks if the list is empty;
bool isEmptyMultiList(MultipleSourceMovesList* lst) {
	return lst->head == NULL;
}

//This function makes an empty linked list;
MultipleSourceMovesListCell* getEmptyMultiList() {
	MultipleSourceMovesList* res = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkAllocation(res);
	res->head = res->tail = NULL;
	return res;
}

//This function creates a new node of "MultipleSourceMovesListCell" type;
MultipleSourceMovesListCell* createNewMultiNode(SingleSourceMovesList* lst) {
	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkAllocation(res);
	res->single_source_moves_list = lst;
	res->next = NULL;
	return res;
}

//This function inserts a node to the end of the linked list;
void insertMultiToEndList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node) {
	if (lst->head == NULL)
		lst->head = lst->tail = node;
	else {
		lst->tail->next = node;
		lst->tail = node;
	}
}

//This function adds a tail to the list, if it was not updated;
void addTailToList(SingleSourceMovesList* lst) {
	SingleSourceMovesListCell* curCell = lst->head;

	while (curCell->next != NULL) {
		curCell = curCell->next;
	}
	lst->tail = curCell;
}

//This function frees the linked list;
void freeMultiList(MultipleSourceMovesList* lst) {
	MultipleSourceMovesListCell* curCell = lst->head;
	while (curCell != NULL)
	{
		SingleSourceMovesListCell* curSingleCell = curCell->single_source_moves_list->head;
		while (curSingleCell != NULL) {
			free(curSingleCell->position);
			SingleSourceMovesListCell* saver = curSingleCell;
			curSingleCell = curSingleCell->next;
			free(saver);
		}
		MultipleSourceMovesListCell* saver = curCell;
		curCell = curCell->next;
		free(saver);
	}
	free(lst);
}

//This function makes a list out of the best possible moves the player can make;
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) {
	MultipleSourceMovesList* res = getEmptyMultiList();
	checkersPos* curPos;
	SingleSourceMovesTree* src;
	SingleSourceMovesList* optimalMove;
	char col, row;
	//run over the board
	for (row = 0; row < 8; row++)
	{
		for (col = 0; col < 8; col++)
		{
			//if found a player
			if (board[row][col] == player) {
				//get its possible moves tree
				curPos = createNewPos(row + 'A', col + '1');
				src = FindSingleSourceMoves(board, curPos);
				//if the player can move
				if (src->source->nextMove[0] != NULL || src->source->nextMove[1] != NULL)
				{
					//find his optimal move, and insert it the the multipleSourceMovesList
					optimalMove = FindSingleSourceOptimalMove(src);
					addTailToList(optimalMove);
					MultipleSourceMovesListCell* newCell = createNewMultiNode(optimalMove);
					insertMultiToEndList(res, newCell);
				}

				free(curPos);
				free(src);
			}
		}
	}
	return res;
}