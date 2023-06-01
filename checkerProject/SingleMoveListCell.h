#include "singleMoveTree.h"
typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;
typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

SingleSourceMovesListCell* createNewListNode(checkersPos* pos, unsigned short captures);
SingleSourceMovesList* getEmptyList();
void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);
void insertNodeToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);
bool isEmptyList(SingleSourceMovesList* lst);
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesListCell* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* root);
int whatPathToChoose(SingleSourceMovesTree* moves_tree);
int whatPathToChooseHelper(SingleSourceMovesTreeNode* source);
void printList(SingleSourceMovesList* lst);
char whichPlayer(checkersPos* pos, SingleSourceMovesTreeNode* source);
void insertDatatoStartList(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* source);
int countNodes(SingleSourceMovesTreeNode* node);