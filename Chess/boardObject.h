#pragma once
#include "piece.h"

class boardObject
{
private:
	piece*** boardArray;

public:
	boardObject(piece*** board);
	piece*** getBoard() { return boardArray; };
	boardObject();
	~boardObject();
};

