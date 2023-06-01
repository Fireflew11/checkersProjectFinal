#ifndef __BOARD_FUNCIONS_H
#define __BOARD_FUNCIONS_H
#include <stdio.h>
#define BOARD_SIZE 8
#define P_M_LINE 19
#define PLAYER_T 'T'
#define PLAYER_B 'B'
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
void copyBoard(Board boardRes, Board boardfrom);
void createBoard(Board res);
void drawPMLine();
void drawBoard(Board board);
#endif
