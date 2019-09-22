#pragma once
#include <string>
#include <nana/gui/wvl.hpp>
#include <iostream>
#include <cmath>

#include "move.h"



class piece
{
protected:
	std::string pieceTextureWhiteOne = "Resources/pawnWhite1.png";
	std::string pieceTextureBlackOne = "Resources/pawnBlack1.png";
	std::string pieceTextureWhiteTwo = "Resources/pawnWhite2.png";
	std::string pieceTextureBlackTwo = "Resources/pawnBlack2.png";
	const double PI = 3.141592654;
	bool displayHighlight = true;
	bool selected = false;
	bool highlighted = false;
	bool madeFirstMove = false;
	bool doubleMoveMade = false;
	bool aiMove = false;
	int pieceWeight = 0;

	bool whiteBackground(int x, int y);
	void restoreBoard(bool originalBoard[2][8][8], piece*** board);






public:
	piece();
	virtual ~piece();
	virtual void possibleMoves(int x, int y, piece*** board, int currentPlayer) {};
	virtual void makeMove(nana::point startLocatiom, nana::point endLocation, piece*** board);

	std::string texture(int x, int y);

	//Getter and setter for selected variable
	void setSelected(bool i) { selected = i; };
	bool getSelected() { return selected; };

	void setHighlighted(bool i){highlighted = i; };
	bool getHighlighted() { return highlighted; };

	int playerOpponent(int currentplayer);
	void clearSelections(piece*** board);

	int player = -1;
	bool displayOffset = false;
	bool threatened = false;

	void setMadeFirstMove(bool i) { madeFirstMove = i; };
	bool getMadeFirstMove() { return madeFirstMove; };

	bool isThreatened(int x, int y, piece*** board, int player);

	bool getDoubleMoveMade() { return doubleMoveMade; };

	int getPieceWeight() { return pieceWeight; };


	bool checkMate(int player, piece*** boardArray);
	void tryMoves(piece*** boardArray, nana::point startLocation, int& solutions);
	bool kingThreatened(piece*** boardArray);

	bool getAIMove() { return aiMove; };
	void setAIMove(bool i) { aiMove = i; };

};
