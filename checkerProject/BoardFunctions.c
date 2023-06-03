#include "BoardFunctions.h"


//This function copies the board everytime after we change it;
void copyBoard(Board boardRes, Board boardfrom) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			boardRes[i][j] = boardfrom[i][j];
		}
	}
}

//This function creates a new board;
void createBoard(Board res) {
	char curChar = PLAYER_T;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i == 3)
			curChar = PLAYER_B;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i < 3 || i > 4) {
				if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
					res[i][j] = curChar;
				}
				else
					res[i][j] = ' ';
			}
			else
				res[i][j] = ' ';

		}
	}
}

//This function draws the plus and minus lines;
void drawPMLine() {
	for (int i = 0; i < P_M_LINE; i++)
	{
		if (i % 2 == 0)
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}

//This function prints the board;
void drawBoard(Board board) {

	int rowCounter = 0;
	for (int i = 0; i < P_M_LINE; i++)
	{
		if (i % 2 == 0)
			drawPMLine();
		else if (i == 1) {
			printf("+ |1|2|3|4|5|6|7|8|\n");
		}
		else {
			printf("|%c|", rowCounter + 'A');
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				printf("%c|", board[rowCounter][j]);
			}
			printf("\n");
			rowCounter++;
		}
	}

}