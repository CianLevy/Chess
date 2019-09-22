#pragma once
#include "piece.h"

class king : public piece{

private:
	void handleCastling(piece*** board);

public:
	king(int owner);
	void possibleMoves(int x, int y, piece*** board, int currentPlayer);
	void makeMove(nana::point startLocatiom, nana::point endLocation, piece*** board);
};

