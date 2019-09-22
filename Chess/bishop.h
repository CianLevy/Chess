#pragma once
#include "piece.h"
class bishop : public piece {
public:
	bishop(int owner);
	//using piece::possibleMoves;
	void possibleMoves(int x, int y, piece*** board, int currentPlayer);
};