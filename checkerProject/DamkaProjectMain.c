//Ido Schneider 209127752
//Tom Braudo 

#include "Turns.h";
#include "BoardFunctions.h"
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1


void main() {

	Board board;
	createBoard(board);
	PlayGame(board, PLAYER_B);

}


