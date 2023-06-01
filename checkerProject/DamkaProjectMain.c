#include "Turns.h";
#include "BoardFunctions.h"
#define TYPE_FLAG_T 1
#define TYPE_FLAG_B -1


//this is main instructions are here
//git instructions:
/*

after finishing a function or a session,
save and close visual studios
then open CMD
then apply these commands:
cd "project-path"
git add .
git commit -m "name-of-the-update" (give meaningfull name, what changed)
git push

and then it will be on the site

*/
//working together instructions:
/*
on every function or we we write, comment so the other could understand what was written, even without asking directly
never commit push something that didn't work in testing/debugging
have fun :)

*/


void main() {
	Board board;
	SingleSourceMovesList* lst;
	SingleSourceMovesTree* tr;
	checkersPos* pos;
	createBoard(board);

	PlayGame(board, 'T');





	/*createBoard(board);*/
	//PlayGame(board, 'T');


}


