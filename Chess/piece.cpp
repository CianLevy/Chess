#include "stdafx.h"
#include "piece.h"


piece::piece(){
	//Default piece is just a blank square
	pieceTextureWhiteOne = "Resources/emptyWhite.png";
	pieceTextureBlackOne = "Resources/emptyBlack.png";
	pieceTextureWhiteTwo = "Resources/emptyWhite.png";
	pieceTextureBlackTwo = "Resources/emptyBlack.png";
}


piece::~piece(){

}

int piece::playerOpponent(int currentplayer) {
	if (currentplayer == 0)
		return 1;
	else 
		return 0;

}

bool piece::whiteBackground(int x, int y) {

	if (y % 2 == 0) {
		if (x % 2 != 0)
			return false;
		else
			return true;
	}
	else {
		if (x % 2 != 0)
			return true;
		else
			return false;
	}

}

std::string piece::texture(int x, int y) {
	bool background = whiteBackground(x, y);

	if (background && player == 0 || (player == -1 && background))
		return pieceTextureWhiteOne;
	else if (background && player == 1)
		return pieceTextureWhiteTwo;
	else if (!background && player == 0 || (player == -1 && !background))
		return pieceTextureBlackOne;
	else
		return pieceTextureBlackTwo;

}

void piece::makeMove(nana::point startLocation, nana::point endLocation, piece*** board) {
	board[endLocation.y][endLocation.x] = board[startLocation.y][startLocation.x];
	board[startLocation.y][startLocation.x] = new piece;

}

bool piece::isThreatened(int x, int y, piece*** board, int player) {
	int kingX, kingY;

	//The initial board state is stored in the boardstates array
	bool boardStates[2][8][8];
	for (int i = 0; i < 8; i++) {
		for (int k = 0; k < 8; k++) {
			if (board[i][k]->getHighlighted()) {
				boardStates[0][i][k] = true;
				boardStates[1][i][k] = false;
			}
			else if (board[i][k]->getSelected()) {
				boardStates[1][i][k] = true;
				boardStates[0][i][k] = false;
			}
			else {
				boardStates[0][i][k] = false;
				boardStates[1][i][k] = false;
			}
	
		}
	}
	clearSelections(board);

	int opponentID = playerOpponent(player);

	for (int i = 0; i < 8; i++) {

		for (int c = 0; c < 8; c++) {

			if (board[i][c]->player == opponentID) {
				if (board[i][c]->displayOffset) {
					for (int direction = 0; direction < 9; direction++) {
						kingX = c + round(cos((PI / 4)*direction));
						kingY = i + round(sin((PI / 4)*direction));

						if (kingX == x && kingY == y) {
							//std::cout << "player " << board[i][c]->player << " x " << c << " y " << i << std::endl;
							restoreBoard(boardStates, board);

							return true;
						}
					}
				}else
					board[i][c]->possibleMoves(c, i, board, opponentID);
			

				if (board[y][x]->getHighlighted()) {
					restoreBoard(boardStates, board);
					return true;
				}
			}

		}
	}
	restoreBoard(boardStates, board);
	return false;
}

void piece::clearSelections(piece*** board) {

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			board[y][x]->setHighlighted(false);
			board[y][x]->setSelected(false);
		}
	}


}


void piece::restoreBoard(bool originalBoard[2][8][8], piece*** board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			board[y][x]->setHighlighted(originalBoard[0][y][x]);
			board[y][x]->setSelected(originalBoard[1][y][x]);
		}
	}
}



bool piece::checkMate(int player, piece*** boardArray) {
	int possibleSolutions = 0;
	nana::point location;

	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {


			if (boardArray[y][x]->player == player) {

				//First find the possible moves for the piece
				boardArray[y][x]->possibleMoves(x, y, boardArray, player);

				location.x = x;
				location.y = y;

				//Then try the moves and count if there are any that break check
				tryMoves(boardArray, location, possibleSolutions);

				clearSelections(boardArray);
			}

			if (possibleSolutions > 0) {
				possibleSolutions = 0;
				return false;
			}
		}
	}



	return true;
}

void piece::tryMoves(piece*** boardArray, nana::point startLocation, int& solutions) {
	piece* storage;


	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {

			if (boardArray[y][x]->getHighlighted()) {
				//Move the piece to the location without calling makeMove to avoid other ramifications
				storage = boardArray[y][x];
				boardArray[y][x] = boardArray[startLocation.y][startLocation.x];
				boardArray[startLocation.y][startLocation.x] = new piece;

				//The move did not take the king out of check and cannot be made
				if (kingThreatened(boardArray))
					storage->setHighlighted(false);
				else
					solutions++;

				//Return the piece to it's original location
				boardArray[startLocation.y][startLocation.x] = boardArray[y][x];
				boardArray[y][x] = storage;
			}
		}
	}
}
bool piece::kingThreatened(piece*** boardArray) {

	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {

			if (boardArray[y][x]->displayOffset && boardArray[y][x]->player == player) {
				boardArray[y][x]->setHighlighted(false);
				if (boardArray[y][x]->isThreatened(x, y, boardArray, player)) {

					return true;
				}
				else
					return false;


			}
		}
	}
}