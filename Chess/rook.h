#pragma once
#include "piece.h"
class rook : public piece {
public:
	rook(int owner);
	//using piece::possibleMoves;
	void possibleMoves(int x, int y, piece*** board, int currentPlayer);

};
