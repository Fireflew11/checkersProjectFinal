#include <stdbool.h>
#include "SingleMoveListCell.h"

//This function creates a new linked list node;
SingleSourceMovesListCell* createNewListNode(checkersPos* pos, unsigned short captures) {
	SingleSourceMovesListCell* res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocation(res);
	res->position = pos;
	res->captures = captures;
	res->next = NULL;
	return res;
}

//This function gets a linked list, and makes it an empty one;
SingleSourceMovesList* getEmptyList() {
	SingleSourceMovesList* res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocation(res);
	res->head = res->tail = NULL;
	return res;
}

//This function inserts a node to the end of the linked list;
void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node) {
	if (lst->tail != NULL) {
		lst->tail->next = node;
		lst->tail = node;
	}
	else
		lst->head = lst->tail = node;
}

//This function checks if the list that was given is empty or not;
bool isEmptyList(SingleSourceMovesList* lst) {

	if (lst->head == NULL)
		return true;
	else
		return false;

}

//This function insters data to the start of the linked list, by creating a node with the data that was provided;
void insertDatatoStartList(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* source) {

	SingleSourceMovesListCell* newHead;
	checkersPos* newPos = createNewPos(source->pos->row, source->pos->col);
	newHead = createNewListNode(newPos, source->total_caprures_so_far);
	insertNodeToStartList(lst, newHead);

}

//This function inserts a node to the start of a linked list;
void insertNodeToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node) {

	if (isEmptyList(lst)) {

		node->next = NULL;
		lst->head = lst->tail = node;

	}
	else {
		node->next = lst->head;
		lst->head = node;

	}
}

//This function builds a linked list that consists the optimal route a player can play;
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {
	SingleSourceMovesList* res = getEmptyList();
	int whatSide;
	char player;

	if (moves_tree != NULL) { // case 1, if there is no tree to begin with;

		whatSide = whatPathToChoose(moves_tree);
		if (whatSide == 1) {// we can only search the right side of the tree;

			res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[1]);
			insertDatatoStartList(res, moves_tree->source); // inserting the "root" of the tree to be the first node in the list;
			return res;
		}
		else if (whatSide == 0) { // we only need to search the left side of the tree;
			res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[0]);
			insertDatatoStartList(res, moves_tree->source);// inserting the "root" of the tree to be the first node in the list;
			return res;
		}
		else {
			player = whichPlayer(moves_tree->source->pos, moves_tree->source->board);
			if (moves_tree->source->nextMove[0]->total_caprures_so_far > moves_tree->source->nextMove[1]->total_caprures_so_far) { // checking what path did the most captures.
				res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[0]);
				insertDatatoStartList(res, moves_tree->source); // inserting the "root" of the tree to be the first node in the list;
				return res;
			}
			else if (moves_tree->source->nextMove[0]->total_caprures_so_far < moves_tree->source->nextMove[1]->total_caprures_so_far) {
				res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[1]);
				insertDatatoStartList(res, moves_tree->source); // inserting the "root" of the tree to be the first node in the list;
				return res;
			}
			else {
				if (player == PLAYER_T) { // go right according to the rule of the game (go closer to col 8) // if its the same amount of captures to each move, then go by rule.
					res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[1]);
					insertDatatoStartList(res, moves_tree->source); // inserting the "root" of the tree to be the first node in the list;
					return res;
				}
				else { // go left according to the rule of the game (go closer to col 0)
					res->head = FindSingleSourceOptimalMoveHelper(res, moves_tree->source->nextMove[0]); 
					insertDatatoStartList(res, moves_tree->source);// inserting the "root" of the tree to be the first node in the list;
					return res;
				}
			}
		}
	}
	else
		return NULL;
}

//This function build a linked lists tha consists out of the optimal route that a player can play;
SingleSourceMovesListCell* FindSingleSourceOptimalMoveHelper(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* source) {

	SingleSourceMovesListCell* leftPath, * rightPath, * newHead;
	int res;

	// case 2; we only have one move to play;
	if (source->nextMove[0] == NULL && source->nextMove[1] == NULL) {
		return createNewListNode(source->pos, source->total_caprures_so_far); // returns a node with the position.
	}
	else if (source->nextMove[0] == NULL) {//case 3; there is no sub left tree, we can only move to the right;
		rightPath = FindSingleSourceOptimalMoveHelper(lst, source->nextMove[1]);
		if (rightPath->position != source->pos) {
			newHead = createNewListNode(source->pos, source->total_caprures_so_far);
			if (isEmptyList(lst)) {
				insertNodeToStartList(lst, newHead);
				insertNodeToEndList(lst, rightPath);
			}
			else
				insertNodeToStartList(lst, newHead);
			return newHead;
		}
		else {
			insertNodeToStartList(lst, rightPath);
			return rightPath;
		}
	}
	else if (source->nextMove[1] == NULL) {//case 4, there is no sub right tree, we can only move left;
		leftPath = FindSingleSourceOptimalMoveHelper(lst, source->nextMove[0]);
		if (leftPath->position != source->pos) {
			newHead = createNewListNode(source->pos, source->total_caprures_so_far);
			if (isEmptyList(lst)) {
				insertNodeToStartList(lst, newHead);
				insertNodeToEndList(lst, leftPath);
			}
			else
				insertNodeToStartList(lst, newHead);
			return newHead;
		}
		else {
			insertNodeToStartList(lst, leftPath);
			return leftPath;
		}
	}
	else { //case 5, there are sub trees to the right and left;
		FindSingleSourceOptimalMove(source);
	}
}

//The function tells us which sub tree is longer(has more levels to it);
int whatPathToChoose(SingleSourceMovesTree* moves_tree) {

	int res;
	if (moves_tree->source != NULL) { //case 1 if there is no tree-

		res = whatPathToChooseHelper(moves_tree->source);
		return res; // 1 if  the right side is longer, 0 if its the left side, -1 if its the same size, -2 if there is no tree;
	}
	res = -2;
	return res;
}

//The function tells us which sub tree is longer(has more levels to it);
int whatPathToChooseHelper(SingleSourceMovesTreeNode* source) {
	if (source == NULL)
		return -1; // If the node is NULL, consider it as a balanced subtree.

	int leftCount = countNodes(source->nextMove[0]);
	int rightCount = countNodes(source->nextMove[1]);

	if (rightCount > leftCount)
		return 1; // If the right subtree is longer.
	else if (leftCount > rightCount)
		return 0; // If the left subtree is longer.
	else
		return -1; // If both sides have the same number of nodes.
}

//This function prints the linked list;
void printList(SingleSourceMovesList* lst) {

	SingleSourceMovesListCell* node;
	if (isEmptyList(lst))
		return;
	node = lst->head;

	while (node->next != NULL) {

		printf("%c%c->%c%c\n", node->position->row, node->position->col, node->next->position->row, node->next->position->col);
		node = node->next;
	}
	printf("\n");
}

//This function returns the type of player that is playing in the called move;
char whichPlayer(checkersPos* pos, SingleSourceMovesTreeNode* source) {

	char rows, cols, type;
	rows = pos->row - 'A';
	cols = pos->col - '1';

	type = source->board[rows][cols];
	return type;
}

//This function counts how many nodes are in a given tree;
int countNodes(SingleSourceMovesTreeNode* node) {
	if (node == NULL)
		return 0;

	int leftCount = countNodes(node->nextMove[0]);
	int rightCount = countNodes(node->nextMove[1]);

	return leftCount + rightCount + 1;
}
