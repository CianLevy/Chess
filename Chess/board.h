#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <iostream>
#include <string>
#include "aiPlayer.h"

#include "piece.h"
#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"


class board {

private:
	nana::form mainForm;
	piece*** boardArray;
	nana::point selectedLocation;
	nana::point previousLocation;

	const int squareSIZE = 80;
	bool pieceSelected = false;

	void handleSelection(const nana::arg_click& arg);


	bool kingThreatened(int player);
	bool check = false;
	bool checkmate = false;

	void tryMoves(int currentPlayer);


	int possibleMoveCounter = 0;
	int turnCounter = 0;

	bool aiGame = true;
	void aiMove();
	aiPlayer test;
	

public:
	void displayBoard();
	void clearSelections();
	bool checkMate(int player);
	board();



};