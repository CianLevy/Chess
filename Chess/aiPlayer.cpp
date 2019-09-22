#include "stdafx.h"
#include "aiPlayer.h"


aiPlayer::aiPlayer()
{
}


aiPlayer::~aiPlayer()
{
}


void aiPlayer::makeMove(piece*** board, move newMove) {
	moveCounter++;
	board[newMove.getEndY()][newMove.getEndX()] = board[newMove.getStartY()][newMove.getStartX()];
	//delete 	board[newMove.getStartY()][newMove.getStartX()];
	board[newMove.getStartY()][newMove.getStartX()] = blankLocation;
}

void aiPlayer::deleteBoard(piece*** board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			delete board[y][x];
		}
		delete board[y];
	}
	delete board;
}


//Calculates total weight which makes AI avoid losing its own pieces
//Return negative values when black is winning
float aiPlayer::calculateBoardWeight(piece*** board, int player) {
	float totalWeight = 0;
	/*std::vector<move> whiteMoves = moveList(board, 0);
	std::vector<move> blackMoves = moveList(board, 1);
	int whiteMobility = whiteMoves.size();
	int blackMobility = blackMoves.size();

	whiteMoves.clear();
	blackMoves.clear();
	int mobilityScore = whiteMobility - blackMobility;
	*/
	
	float score;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			//std::cout << locationValue(board, x, y) << std::endl;
				totalWeight += board[y][x]->getPieceWeight() + locationValue(board, x, y);
		}
	}
	//std::cout << totalWeight << " " << numberofgames << std::endl;
	score = totalWeight;
	//std::cout << "Board evaluation " << score << std::endl;
	if (player == 1)
		return score;
	else
		return -score;


}
float aiPlayer::alphaBeta(static piece*** board, int depth, float alpha, float beta, int player, move& bestMove) {
	float evaluation;
	if (depth == 0) {
		evaluation = -calculateBoardWeight(board, player);
		return evaluation;
	}
	float best = -901;
	
	std::vector<move> allPossibleMoves = moveList(board, player);

	for (int i = 0; i < allPossibleMoves.size(); i++) {
		boardObject newBoard(board);
		makeMove(newBoard.getBoard(), allPossibleMoves[i]);

		evaluation = -alphaBeta(newBoard.getBoard(), depth - 1, -beta, -alpha, board[0][0]->playerOpponent(player), bestMove);

		//if (depth == 3)
		//	std::cout << "Evaluation " << evaluation << std::endl;
		if (evaluation > best) {
			best = evaluation;
	
			if (depth == searchDepth) {
				bestMove = allPossibleMoves[i];

			}
		}
		if (best > alpha) {
			alpha = best;
		}
		if (best >= beta) {
			//deleteBoard(newBoard.getBoard());
			break;
		}

	}
	//allPossibleMoves.erase(allPossibleMoves.begin() + allPossibleMoves.size());
	allPossibleMoves.clear();

	return best;
}

std::vector<move> aiPlayer::moveList(piece*** board, int player) {
	std::vector<move> possibleMoves;
	
	int totalMoves = 0, currentPieceMoves = 0;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			
			if (board[y][x]->player == player) {
				board[y][x]->possibleMoves(x, y, board, player);
				board[y][x]->tryMoves(board, nana::point(x,y), currentPieceMoves);
				//std::cout << "move list moves: " << currentPieceMoves << std::endl;
				if (currentPieceMoves > 0) {
					totalMoves += currentPieceMoves;

					//Loop through possible locations and add moves to the array
					for (int y2 = 0; y2 < 8; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if (board[y2][x2]->getHighlighted()) {
					
								possibleMoves.push_back(move(x, y, x2, y2));
					
							}
						}
					}
					currentPieceMoves = 0;

				}
				//After the moves have been added clear the board for the next loop
				board[0][0]->clearSelections(board);

			}

		}
	}
	return possibleMoves;
}

piece*** aiPlayer::createBoardCopy(piece*** board) {
	piece*** newBoard = new piece**[8];

	for (int i = 0; i < 8; i++) {

		newBoard[i] = new piece*[8];

		for (int x = 0; x < 8; x++)

			newBoard[i][x] = board[i][x];
	}


	return newBoard;
}


float aiPlayer::locationValue(piece*** board, int x, int y) {
	float temp;

	/*if (board[y][x]->player == 0)
		std::cout << "White " << 8 * y + x << std::endl;
	else if (board[y][x]->player == 1)
		std::cout << "Black " << 56 - 8 * y + x << std::endl;
		*/

	if (board[y][x]->player == 0 && ((8 * y + x) >= 64 || (8 * y + x) < 0))
		std::cout << "Out of bounds for player 0 " << (8 * y + x) << std::endl;
	else if (board[y][x]->player == 1 && ((56 - 8 * y + x) < 0 || (56 - 8 * y + x) >= 64))
		std::cout << "Out of bounds for player 1 " << (56 - 8 * y + x) << std::endl;
		


	switch (board[y][x]->getPieceWeight())
	{
	default:
		temp = 0;
		break;
	case (10):
		temp = pawnEvalWhite[8 * y + x];
		break;
	case (-10):
		temp = pawnEvalWhite[56 - 8 * y + x];
		break;
	case (30):
		if (board[y][x]->getDoubleMoveMade())
			temp = knightEval[8 * y + x];
		else
			temp = bishopEvalWhite[8 * y + x];
		break;
	case (-30):
		if (board[y][x]->getDoubleMoveMade())
			temp = knightEval[56 - 8 * y + x];
		else
			temp = bishopEvalWhite[56 - 8 * y + x];
		break;
	case (50):
		temp = rookEvalWhite[8 * y + x];
		break;
	case (-50):
		temp = rookEvalWhite[56 - 8 * y + x];
		break;
	case (90):
		temp = queenEvalWhite[8 * y + x];
		break;
	case (-90):
		temp = queenEvalWhite[56 - 8 * y + x];
		break;
	case (900):
		temp = kingEvalWhite[8 * y + x];
		break;
	case (-900):
		temp = kingEvalWhite[56 - 8 * y + x];
		break;

	}
	return temp;
}