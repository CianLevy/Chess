#include "stdafx.h"
#include "king.h"

king::king(int owner) {
	displayOffset = true;
	pieceTextureWhiteOne = "Resources/kingWhite1.png";
	pieceTextureBlackOne = "Resources/kingBlack1.png";
	pieceTextureWhiteTwo = "Resources/kingWhite2.png";
	pieceTextureBlackTwo = "Resources/kingBlack2.png";
	player = owner;
	pieceWeight = 900 * pow(-1, owner);

}

void king::possibleMoves(int x, int y, piece*** board, int currentPlayer) {
	int cosine, sine;
	piece* storage;
	bool moveStatus = madeFirstMove;

	for (int direction = 0; direction < 9; direction++) {
		cosine = round(cos((PI / 4)*direction));
		sine = round(sin((PI / 4)*direction));

		if (y + sine >= 0 && y + sine < 8 && x + cosine >= 0 && x + cosine < 8) {

			if (board[y + sine][x + cosine]->player == -1 || board[y + sine][x + cosine]->player == playerOpponent(currentPlayer)) {
				//Move the king to the location
				storage = board[y + sine][x + cosine];
				makeMove(nana::point(x, y), nana::point(x + cosine, y + sine), board);

				if (!isThreatened(x + cosine, y + sine, board, currentPlayer))
					storage->setHighlighted(true);

				//return king to previous location
				board[y][x] = board[y + sine][x + cosine];
				board[y + sine][x + cosine] = storage;
				board[y][x]->setMadeFirstMove(moveStatus);

			}
		}
	}
	handleCastling(board);

	board[y][x]->setSelected(true);
}

void king::makeMove(nana::point startLocation, nana::point endLocation, piece*** board) {

	board[startLocation.y][startLocation.x]->setMadeFirstMove(true);

	if (endLocation.x - startLocation.x == 2) {
		piece* storage = board[endLocation.y][endLocation.x + 1];
		board[endLocation.y][endLocation.x + 1] = new piece;
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
		board[startLocation.y][startLocation.x] = new piece;
		board[startLocation.y][startLocation.x + 1] = storage;

	}
	else if (endLocation.x - startLocation.x == -2) {
		piece* storage = board[endLocation.y][endLocation.x - 2];
		board[endLocation.y][endLocation.x - 2] = new piece;
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
		board[startLocation.y][startLocation.x] = new piece;
		board[startLocation.y][startLocation.x - 1] = storage;
	}
	else {
		board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
		board[startLocation.y][startLocation.x] = new piece;

	}
}


void king::handleCastling(piece*** board) {
	nana::point rookOneLocation(0, 0);
	nana::point rookTwoLocation(7, 0);
	nana::point kingLocation(4, 0);
	bool castle = true;

	if (player == 0) {
		rookOneLocation.y = 7;
		rookTwoLocation.y = 7;
		kingLocation.y = 7;
	}

	if (!madeFirstMove && !board[rookOneLocation.y][rookOneLocation.x]->getMadeFirstMove() && 
		board[rookOneLocation.y][rookOneLocation.x]->player == player && board[rookOneLocation.y][rookOneLocation.x]->getDoubleMoveMade()) {
		for (int x = rookOneLocation.x; x <= kingLocation.x; x++) {
			if (isThreatened(x, kingLocation.y, board, player))
				castle = false;
			else if (x != rookOneLocation.x && x != kingLocation.x && board[kingLocation.y][x]->player != -1)
				castle = false;
		}

		//If castling is not allowed the the bool will already be set to false
		if (castle) {
			board[kingLocation.y][rookOneLocation.x + 2]->setHighlighted(true);
		}
		castle = true;

	}
	if (!madeFirstMove && !board[rookTwoLocation.y][rookTwoLocation.x]->getMadeFirstMove() &&
		board[rookTwoLocation.y][rookTwoLocation.x]->player == player && board[rookTwoLocation.y][rookTwoLocation.x]->getDoubleMoveMade()) {

		for (int x = rookTwoLocation.x; x >= kingLocation.x; x--) {

			if (isThreatened(x, kingLocation.y, board, player))
				castle = false;
			else if (x != rookTwoLocation.x && x != kingLocation.x && board[kingLocation.y][x]->player != -1)
				castle = false;
		}

		if (castle) {
			board[kingLocation.y][rookTwoLocation.x - 1]->setHighlighted(true);

		}
	}

}