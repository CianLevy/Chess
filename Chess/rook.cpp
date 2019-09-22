#include "stdafx.h"
#include "rook.h"

rook::rook(int owner) {
	pieceTextureWhiteOne = "Resources/rookWhite1.png";
	pieceTextureBlackOne = "Resources/rookBlack1.png";
	pieceTextureWhiteTwo = "Resources/rookWhite2.png";
	pieceTextureBlackTwo = "Resources/rookBlack2.png";
	player = owner;
	doubleMoveMade = true;
	pieceWeight = 50 * pow(-1, owner);
}

void rook::possibleMoves(int x, int y, piece*** board, int currentPlayer) {
	int cosine, sine;

	for (int direction = 0; direction < 4; direction++) {
		//Storing cosine and sine is less computationally intensive
		cosine = cos((PI / 2)*direction);
		sine = sin((PI / 2)*direction);

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

