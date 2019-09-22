#include "stdafx.h"
#include "queen.h"


queen::queen(int owner) {
	pieceTextureWhiteOne = "Resources/queenWhite1.png";
	pieceTextureBlackOne = "Resources/queenBlack1.png";
	pieceTextureWhiteTwo = "Resources/queenWhite2.png";
	pieceTextureBlackTwo = "Resources/queenBlack2.png";
	player = owner;
	pieceWeight = 90 * pow(-1, owner);
}

void queen::possibleMoves(int x, int y, piece*** board, int currentPlayer) {
	int cosine;
	int sine;

	for (int direction = 0; direction < 9; direction++) {
		cosine = round(cos((PI / 4)*direction));
		sine = round(sin((PI / 4)*direction));

		for (int distance = 1; distance < 8; distance++) {
			if (y + sine*distance >= 0 && y + sine*distance < 8 && x + cosine*distance >= 0 && x + cosine*distance < 8) {
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