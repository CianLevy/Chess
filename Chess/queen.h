#pragma once
#include "piece.h"

class queen : public piece {
public:
	queen(int owner);

	void possibleMoves(int x, int y, piece*** board, int currentPlayer);
};