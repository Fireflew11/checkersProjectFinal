#ifndef __SINGLE_MOVE_TREE_H
#define __SINGLE_MOVE_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1
#define BOARD_SIZE 8
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _checkersPos
{
	char row, col;
}checkersPos;
typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_caprures_so_far;
	struct _SingleSourceMovesTreeNode* nextMove[2];
}SingleSourceMovesTreeNode;
typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;

}SingleSourceMovesTree;


void checkAllocation(void* ptr);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type, unsigned short totalCapsSoFar);
SingleSourceMovesTreeNode* createNewNode(checkersPos* pos, Board board, unsigned short total_caprures_so_far,
	SingleSourceMovesTreeNode* nextmove0, SingleSourceMovesTreeNode* nextmove1);
void updateNextAndBoard(checkersPos* nextPos, SingleSourceMovesTreeNode** nextMove,
	char type, Board board, unsigned short totalCapsSoFar, int typeFlag, int sideFlag);
checkersPos* createNewPos(char row, char col);

int getTreeHeight(SingleSourceMovesTreeNode* source);

int getFlagType(char type);
char getOtherType(char type);



#endif
