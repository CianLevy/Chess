#include "stdafx.h"
#include "bishop.h"


bishop::bishop(int owner) {
	pieceTextureWhiteOne = "Resources/bishopWhite1.png";
	pieceTextureBlackOne = "Resources/bishopBlack1.png";
	pieceTextureWhiteTwo = "Resources/bishopWhite2.png";
	pieceTextureBlackTwo = "Resources/bishopBlack2.png";
	player = owner;
	pieceWeight = 30 * pow(-1, owner);
}

void bishop::possibleMoves(int x, int y, piece*** board, int currentPlayer) {
	int cosine;
	int sine;

	for (int direction = 0; direction < 4; direction++) {
		cosine = 1.5*cos(PI / 4 + (PI / 2)*direction);
		sine = 1.5*sin(PI / 4 + (PI / 2)*direction);

		for (int distance = 1; distance < 8; distance++) {
			if (y + sine*distance >= 0 && y + sine*distance < 8 && x + cosine*distance >= 0 && x + cosine*distance < 8) {
				//-1 indicates that the tile is empty, so the move is possible
				if (board[y + sine*distance][x + cosine*distance]->player == -1) {
					board[y + sine*distance][x + cosine*distance]->setHighlighted(true);
				}
				else if (board[y + sine*distance][x + cosine*distance]->player == playerOpponent(currentPlayer)) {
					board[y + sine*distance][x + cosine*distance]->setHighlighted(true);
					break;
				}
				else
					break;
			}
			else
				break;
		}

	}
	board[y][x]->setSelected(true);
}