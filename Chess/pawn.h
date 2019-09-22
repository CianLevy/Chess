#pragma once
#include "piece.h"

class pawn : public piece {

private:

	int playDirection(int currentplayer);

public:

	pawn(int owner);
	void possibleMoves(int x, int y, piece*** board, int currentPlayer);
	void makeMove(nana::point startLocatiom, nana::point endLocation, piece*** board);

};

