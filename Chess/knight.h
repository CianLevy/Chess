#pragma once
#include "piece.h"
class knight : public piece {

public:
	knight(int owner);
	//using piece::possibleMoves;
	void possibleMoves(int x, int y, piece*** board, int currentPlayer);

};



