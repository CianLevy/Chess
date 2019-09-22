#pragma once
class move
{
private:
	int startX;
	int startY;
	int endX;
	int endY;

public:

	move(int x1, int y1, int x2, int y2);
	~move();
	void add(int x1, int y1, int x2, int y2);

	int getStartX() { return startX; };
	int getStartY() { return startY; };

	int getEndX() { return endX; };
	int getEndY() { return endY; };

};

