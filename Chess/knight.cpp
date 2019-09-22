#include "stdafx.h"
#include "knight.h"


knight::knight(int owner) {
	pieceTextureWhiteOne = "Resources/knightWhite1.png";
	pieceTextureBlackOne = "Resources/knightBlack1.png";
	pieceTextureWhiteTwo = "Resources/knightWhite2.png";
	pieceTextureBlackTwo = "Resources/knightBlack2.png";
	player = owner;
	pieceWeight = 30 * pow(-1, owner);
	doubleMoveMade = true;
}

void knight::possibleMoves(int x, int y, piece*** board, int currentPlayer) {

	if (y + 2 < 8 && x + 1 < 8 && (board[y + 2][x + 1]->player == playerOpponent(currentPlayer) || board[y + 2][x + 1]->player == -1)) {
		board[y + 2][x + 1]->setHighlighted(true);

	}
	if (y + 2 < 8 && x - 1 >= 0 && (board[y + 2][x - 1]->player == playerOpponent(currentPlayer) || board[y + 2][x - 1]->player == -1)) {
		board[y + 2][x - 1]->setHighlighted(true);
	}
	if (y - 2 >= 0 && x + 1 < 8 && (board[y - 2][x + 1]->player == playerOpponent(currentPlayer) || board[y - 2][x + 1]->player == -1)) {
		board[y - 2][x + 1]->setHighlighted(true);
	}
	if (y - 2 >= 0 && x - 1 >= 0 && (board[y - 2][x - 1]->player == playerOpponent(currentPlayer) || board[y - 2][x - 1]->player == -1))
		board[y - 2][x - 1]->setHighlighted(true);

	if (y + 1 < 8 && x + 2 < 8 && (board[y + 1][x + 2]->player == playerOpponent(currentPlayer) || board[y + 1][x + 2]->player == -1))
		board[y + 1][x + 2]->setHighlighted(true);

	if (y + 1 < 8 && x - 2 >= 0 && (board[y + 1][x - 2]->player == playerOpponent(currentPlayer) || board[y + 1][x - 2]->player == -1))
		board[y + 1][x - 2]->setHighlighted(true);

	if (y - 1 >= 0 && x + 2 < 8 && (board[y - 1][x + 2]->player == playerOpponent(currentPlayer) || board[y - 1][x + 2]->player == -1))
		board[y - 1][x + 2]->setHighlighted(true);

	if (y - 1 >= 0 && x - 2 >= 0 && (board[y - 1][x - 2]->player == playerOpponent(currentPlayer) || board[y - 1][x - 2]->player == -1))
		board[y - 1][x - 2]->setHighlighted(true);

	board[y][x]->setSelected(true);

}

