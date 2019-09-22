#include "stdafx.h"
#include "boardObject.h"


boardObject::boardObject()
{
	boardArray = new piece**[8];
	for (int y = 0; y < 8; y++) {
		boardArray[y] = new piece*[8];
		for (int x = 0; x < 8; x++) {
			boardArray[y][x] = new piece;
		}
	}
}
boardObject::boardObject(piece*** board) {
	/*piece temp;
	piece* test;
	//temp = (*test);
	int test2;
	int* test3;
	test2 = *test3;*/

	boardArray = new piece**[8];

	for (int y = 0; y < 8; y++) {

		boardArray[y] = new piece*[8];

		for (int x = 0; x < 8; x++) {
			//temp = *(board[y][x]);
			boardArray[y][x] = board[y][x];
		}
	}
}

boardObject::~boardObject()
{
	for (int y = 0; y < 8; y++) {
		/*for (int x = 0; x < 8; x++) {
			delete boardArray[y][x];
		}*/
		delete boardArray[y];
	}
	delete boardArray;
}
