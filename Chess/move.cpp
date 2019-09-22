#include "stdafx.h"
#include "move.h"


move::move(int x1, int y1, int x2, int y2){
	startX = x1;
	startY = y1;

	endX = x2;
	endY = y2;

}


move::~move()
{
}

void move::add(int x1, int y1, int x2, int y2) {
	startX = x1;
	startY = y1;

	endX = x2;
	endY = y2;
}