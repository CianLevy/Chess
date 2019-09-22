#pragma once
#include "stdafx.h"
#include "move.h"
#include "piece.h"
#include <iostream>
#include <string>
#include "boardObject.h"

class aiPlayer
{


private:
	int searchDepth = 3;
	
	void deleteBoard(piece*** board);
	piece* blankLocation = new piece;


	float locationValue(piece*** board, int x, int y);

	//Convert with location = 8*y + x
	//For reverse 64 - 8*y + x
	float pawnEvalWhite[64] = { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
		5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
		1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
		0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
		0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
		0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
		0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5,
		0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0 };

	float knightEval[64] = { -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
		-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
		-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
		-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
		-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
		-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
		-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
		-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0 };

	float bishopEvalWhite[64] = { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
		-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0,
		-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0,
		-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0,
		-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,
		-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0,
		-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0 };

	float rookEvalWhite[64] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5,
		-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
		-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
		-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
		-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
		-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
		0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0 };

	float queenEvalWhite[64] = { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
		-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
		-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
		-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
		0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
		-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
		-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
		-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0 };


	float kingEvalWhite[64] = { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
		-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
		-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
		-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
		-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
		-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
		2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0,
		2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0 };

public:
	aiPlayer();
	~aiPlayer();
	float calculateBoardWeight(piece*** board, int player);

	piece*** createBoardCopy(piece*** board);

	float alphaBeta(piece*** board, int depth, float alpha, float beta, int player, move& bestMove);
	std::vector<move> moveList(piece*** board, int player);
	void makeMove(piece*** board, move newMove);
	int moveCounter = 0;

	//int alphaBetav2(piece*** board, int depth, int alpha, int beta, move& bestMove, int player);

};

/*
int aiPlayer::alphaBetav2(piece*** board, int depth, int alpha, int beta, move& bestMove, int player) {
	std::cout << "alpha " << alpha << " beta " << beta << std::endl;
	int evaluation;

	if (depth == 0 || board[0][0]->checkMate(player, board)) {
		evaluation = calculateBoardWeight(board, player);
		return evaluation;
	}
	std::cout << "Board Count " << numberofgames << std::endl;
	std::vector<move> allPossibleMoves = moveList(board, player);
	//std::cout << "x1: " << allPossibleMoves[0].getStartX() << " y1: " << allPossibleMoves[0].getStartY();
	//std::cout << " x " << allPossibleMoves[0].getEndX() << " y " << allPossibleMoves[0].getEndY() << std::endl;

	if (player == 0) {
		for (int i = 0; i < allPossibleMoves.size(); i++) {
			piece*** nextBoard = createBoardCopy(board);
			makeMove(nextBoard, allPossibleMoves[i]);

			evaluation = alphaBetav2(nextBoard, depth - 1, beta, alpha, bestMove, board[0][0]->playerOpponent(player));
			std::cout << "evaluation " << evaluation << std::endl;
			if (evaluation < beta) {
				beta = evaluation;
			//	std::cout << "x1 " << allPossibleMoves[i].getStartX() << " y1 " << allPossibleMoves[i].getStartY() << " x2 " << allPossibleMoves[i].getEndX() << " y2 " << allPossibleMoves[i].getEndY() << std::endl;
				bestMove = allPossibleMoves[i];
				//bestMove.add(allPossibleMoves[i].getStartX(), allPossibleMoves[i].getStartY(), allPossibleMoves[i].getEndX(), allPossibleMoves[i].getEndY());
				//std::cout << "bestmove values " << bestMove.getStartX() << " " << bestMove.getStartY() << " " << bestMove.getEndX() << " " << bestMove.getEndY() << std::endl;
			}
			if (alpha >= beta)
				break;
		}

		return beta;
	}
	else {
		for (int i = 0; i < allPossibleMoves.size(); i++) {
			piece*** nextBoard = createBoardCopy(board);
			makeMove(nextBoard, allPossibleMoves[i]);
			evaluation = alphaBetav2(nextBoard, depth - 1, beta, alpha, bestMove, board[0][0]->playerOpponent(player));
			std::cout << "evaluation " << evaluation << std::endl;
			if (evaluation > alpha) {
				alpha = evaluation;
				bestMove = allPossibleMoves[i];
				std::cout << "x1 " << allPossibleMoves[i].getStartX() << " y1 " << allPossibleMoves[i].getStartY() << " x2 " << allPossibleMoves[i].getEndX() << " y2 " << allPossibleMoves[i].getEndY() << std::endl;
				//bestMove.add(allPossibleMoves[i].getStartX(), allPossibleMoves[i].getStartY(), allPossibleMoves[i].getEndX(), allPossibleMoves[i].getEndY());
				std::cout << "bestmove values " << bestMove.getStartX() << " " << bestMove.getStartY() << " " << bestMove.getEndX() << " " << bestMove.getEndY() << std::endl;

			}
			if (alpha >= beta)
				break;
		}
		return alpha;
	}

}
*/