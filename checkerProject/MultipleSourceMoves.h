#ifndef __MULTIPLE_SOURCE_MOVES
#define __MULTIPLE_SOURCE_MOVES_H
#include "SingleMoveListCell.h"
typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
}MultipleSourceMovesListCell;
typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
}MultipleSourceMovesList;

void insertMultiToEndList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node);
MultipleSourceMovesListCell* getEmptyMultiList();
bool isEmptyMultyList(MultipleSourceMovesList* lst);
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
MultipleSourceMovesListCell* createNewMultiNode(SingleSourceMovesList* lst);
void freeMultiList(MultipleSourceMovesList* lst);
#endif