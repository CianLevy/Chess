#include "stdafx.h"
#include "pawn.h"
#include "queen.h"

pawn::pawn(int owner) {
	pieceTextureWhiteOne = "Resources/pawnWhite1.png";
	pieceTextureBlackOne = "Resources/pawnBlack1.png";
	pieceTextureWhiteTwo = "Resources/pawnWhite2.png";
	pieceTextureBlackTwo = "Resources/pawnBlack2.png";
	player = owner;
	pieceWeight = 10 * pow(-1, owner);
}

int pawn::playDirection(int currentplayer) {
	if (currentplayer == 0)
		return -1;
	else
		return 1;

}

void pawn::possibleMoves(int x, int y, piece*** board, int currentPlayer) {
	//Storing play direction to avoid calling playDirection multiple times
	int direction = playDirection(currentPlayer);

	if (y + direction >= 0 && y + direction < 8 && board[y + direction][x]->player == -1) {
		board[y + direction][x]->setHighlighted(true);

		if (!madeFirstMove && y + 2 * direction >= 0 && y + 2*direction < 8 && board[y + 2 * direction][x]->player == -1)
			board[y + 2 * direction][x]->setHighlighted(true);
	}
	if (y + direction >= 0 && y + direction < 8 && x - 1 >= 0 && board[y + direction][x - 1]->player == playerOpponent(currentPlayer))
		board[y + direction][x - 1]->setHighlighted(true);

	if (y + direction >= 0 && y + direction < 8 && x + 1 < 8 && board[y + direction][x + 1]->player == playerOpponent(currentPlayer))
		board[y + direction][x + 1]->setHighlighted(true);

	//En passant handling
	if (x - 1 >= 0 && y+direction >= 0 && y+direction < 8 && player == board[y - direction][x - 1]->player &&
		board[y][x - 1]->player == playerOpponent(currentPlayer) && board[y][x - 1]->getDoubleMoveMade())
		board[y + direction][x - 1]->setHighlighted(true);

	if (x + 1 < 8 && player == board[y - direction][x + 1]->player &&
		board[y][x + 1]->player == playerOpponent(currentPlayer) && board[y][x + 1]->getDoubleMoveMade())
		board[y + direction][x + 1]->setHighlighted(true);

	board[y][x]->setSelected(true);
}

void pawn::makeMove(nana::point startLocation, nana::point endLocation, piece*** board) {
	madeFirstMove = true;

	if (player == 0 && endLocation.y == 0)
		board[endLocation.y][endLocation.x] = new queen(0);
	else if (player == 1 && endLocation.y == 7)
		board[endLocation.y][endLocation.x] = new queen(1);
	else
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];

	if (startLocation.y - endLocation.y == 2 || startLocation.y - endLocation.y == -2)
		doubleMoveMade = true;
	else
		doubleMoveMade = false;

	//En passant move handling
	if (startLocation.x - 1 >= 0 && player == board[startLocation.y - playDirection(player)][startLocation.x - 1]->player
		&& board[startLocation.y][startLocation.x - 1]->player == playerOpponent(player) && board[startLocation.y][startLocation.x - 1]->getDoubleMoveMade()
		&& endLocation.y == startLocation.y + playDirection(player) && endLocation.x == startLocation.x - 1) {
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
		board[startLocation.y][startLocation.x - 1] = new piece;
	}
	if (startLocation.x + 1 < 8 && player == board[startLocation.y - playDirection(player)][startLocation.x + 1]->player
		&& board[startLocation.y][startLocation.x + 1]->player == playerOpponent(player) && board[startLocation.y][startLocation.x + 1]->getDoubleMoveMade()
		&& endLocation.y == startLocation.y + playDirection(player) && endLocation.x == startLocation.x + 1) {
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
		board[startLocation.y][startLocation.x + 1] = new piece;
	}

	board[startLocation.y][startLocation.x] = new piece;

}