#include "singleMoveTree.h"
#include <stdbool.h>


//col and row are 0-7 for comfort
//This function checks allocation of data;
void checkAllocation(void* ptr) {
	if (ptr == NULL)
	{
		printf("Allocation failed!");
		exit(1);
	}
}

//This function creates and returns a tree of moves by using the function "FindSingleSourcesMovesHelper";
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	SingleSourceMovesTree* res = NULL;
	int row = src->row - 'A';
	int col = src->col - '1';
	if (board[src->row - 'A'][src->col - '1'] != ' ')
	{
		res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAllocation(res);
		res->source = FindSingleSourcesMovesHelper(board, src, board[src->row - 'A'][src->col - '1'], 0);
	}
	return res;
}

//This function builds and returns the tree of moves that a single player can play;
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos* src, char type, unsigned short totalCapsSoFar) {
	SingleSourceMovesTreeNode* nextMoveLeft = NULL, * nextMoveRight = NULL, * res;
	checkersPos* nextLeftPos = NULL, * nextRightPos = NULL;
	int typeFlag = getFlagType(type);
	char otherType = getOtherType(type);
	bool isLeftEdge = false, isRightEdge = false;
	//no piece
	if (src->col == '1') {
		nextLeftPos = NULL;
		isLeftEdge = true;

	}
	else if (src->col == '8') {
		nextRightPos = NULL;
		isRightEdge = true;

	}
	if (!isRightEdge) {
		//if 1 move to the right is space, and no captures so far, we can move to it
		if (board[src->row + typeFlag - 'A'][src->col + 1 - '1'] == ' ' && totalCapsSoFar == 0)
			nextRightPos = createNewPos(src->row + typeFlag, src->col + 1);
		//if 1 move to the right is enemy piece and space after it (make sure no edge after it), we can capture it
		else if (board[src->row + typeFlag - 'A'][src->col + 1 - '1'] == otherType &&
			(src->col != '7' && !(src->row == 'G' && type == PLAYER_T) && !(src->row == PLAYER_B && type == PLAYER_B) && board[src->row + 2 * typeFlag - 'A'][src->col + 2 - '1'] == ' '))
			nextRightPos = createNewPos(src->row + 2 * typeFlag, src->col + 2);
		//else we can't move
		else
			nextRightPos = NULL;
	}
	if (!isLeftEdge) {
		//if 1 move to the left is space, and no captures so far, we can move to it
		if (board[src->row + typeFlag - 'A'][src->col - 1 - '1'] == ' ' && totalCapsSoFar == 0)
			nextLeftPos = createNewPos(src->row + typeFlag, src->col - 1);
		//if 1 move to the left is enemy piece and space after it (make sure no edge after it), we can capture it
		else if (board[src->row + typeFlag - 'A'][src->col - 1 - '1'] == otherType &&
			(src->col != '2' && !(src->row == 'G' && type == PLAYER_T) && !(src->row == PLAYER_B && type == PLAYER_B) && board[src->row + 2 * typeFlag - 'A'][src->col - 2 - '1'] == ' '))
			nextLeftPos = createNewPos(src->row + 2 * typeFlag, src->col - 2);
		//else we can't move
		else
			nextLeftPos = NULL;
	}
	updateNextAndBoard(nextLeftPos, &nextMoveLeft, type, board, totalCapsSoFar, typeFlag, 1);
	updateNextAndBoard(nextRightPos, &nextMoveRight, type, board, totalCapsSoFar, typeFlag, -1);
	res = createNewNode(src, board, totalCapsSoFar, nextMoveLeft, nextMoveRight);

	return res;


}

//This function creates a new node of SingleSourceMovesTreeNode type;
SingleSourceMovesTreeNode* createNewNode(checkersPos* pos, Board board, unsigned short total_caprures_so_far,
	SingleSourceMovesTreeNode* nextmove0, SingleSourceMovesTreeNode* nextmove1)
{
	SingleSourceMovesTreeNode* res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(res);
	copyBoard(res->board, board);
	res->pos = pos;
	res->total_caprures_so_far = total_caprures_so_far;
	(res->nextMove)[0] = nextmove0;
	(res->nextMove)[1] = nextmove1;
	return res;
}

//This function updates the board after everymove;
//typeFlag is 1 if type == PLAYER_T and -1 if type == PLAYER_B
//sideFlag is 1 if called with left move, and -1 if called with right move
void updateNextAndBoard(checkersPos* nextPos, SingleSourceMovesTreeNode** nextMove,
	char type, Board board, unsigned short totalCapsSoFar, int typeFlag, int sideFlag) {
	if (nextPos != NULL) {
		//need new board to update and send, (we also copy in create new node to not lose the array)
		Board newBoard;
		copyBoard(newBoard, board);
		//put the type in its new place and remove the one right (top or bottom from it) whether it was taken or just the piece that made 1 move
		char squareBeforeType = newBoard[nextPos->row - typeFlag - 'A'][nextPos->col + sideFlag - '1'];
		newBoard[nextPos->row - 'A'][nextPos->col - '1'] = type;
		newBoard[nextPos->row - typeFlag - 'A'][nextPos->col + sideFlag - '1'] = ' ';
		//if the piece just moved and not taken, just create the node as a leaf
		if (squareBeforeType == type) {
			*nextMove = createNewNode(nextPos, newBoard, totalCapsSoFar, NULL, NULL);
		}
		//else the piece took an enemy piece so we already removed the enemy piece from board, need to remove the piece that moved from board
		//the piece now continues using the recursion, and build its own tree, with totalCapsSoFar + 1, and the updated board
		else {
			newBoard[nextPos->row - 2 * typeFlag - 'A'][nextPos->col + 2 * sideFlag - '1'] = ' ';
			*nextMove = FindSingleSourcesMovesHelper(newBoard, nextPos, type, totalCapsSoFar + 1);
		}
	}
}

//this function creates a position using row and col;
checkersPos* createNewPos(char row, char col) {
	checkersPos* res = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocation(res);
	res->col = col;
	res->row = row;
	return res;
}

// This function returns who is the player who is playing as a number;
int getFlagType(char type) {
	if (type == PLAYER_T)
		return TYPE_FLAG_T;
	else
		return TYPE_FLAG_B;
}

//This function returns who is the other player that is not playing this turn;
char getOtherType(char type) {
	if (type == PLAYER_T)
		return PLAYER_B;
	else
		return PLAYER_T;
}