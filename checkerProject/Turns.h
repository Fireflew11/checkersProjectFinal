#ifndef __TURNS_H
#define __TURNS_H
#include "MultipleSourceMoves.h"
void Turn(Board board, Player player);
void updateBoardWithMove(Board board, Player player, SingleSourceMovesList* movesList);
int getSideFlag(int side);
void PlayGame(Board board, Player starting_player);
#endif