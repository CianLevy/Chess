#include "stdafx.h"
#include "board.h"




//Constructor to create an 8x8 board as required for chess
board::board() {
	int playerOne = 0, playerTwo = 1;
	boardArray = new piece**[8];

	for (int i = 0; i < 8; i++) {
		boardArray[i] = new piece*[8];
		for (int x = 0; x < 8; x++)
			boardArray[i][x] = new piece;
	}

	//Creating two rows of pawns
	for (int i = 0; i < 8; i++) {
		boardArray[1][i] = new pawn(playerTwo);	
		boardArray[6][i] = new pawn(playerOne);

	}
	//Adding all other pieces to the board for both players
	boardArray[0][0] = new rook(playerTwo);
	boardArray[0][7] = new rook(playerTwo);

	boardArray[0][1] = new knight(playerTwo);
	boardArray[0][6] = new knight(playerTwo);

	boardArray[0][2] = new bishop(playerTwo);
	boardArray[0][5] = new bishop(playerTwo);

	boardArray[0][3] = new queen(playerTwo);
	boardArray[0][4] = new king(playerTwo);

	boardArray[7][0] = new rook(playerOne);
	boardArray[7][7] = new rook(playerOne);

	boardArray[7][1] = new knight(playerOne);
	boardArray[7][6] = new knight(playerOne);

	boardArray[7][2] = new bishop(playerOne);
	boardArray[7][5] = new bishop(playerOne);


	boardArray[7][3] = new queen(playerOne);
	boardArray[7][4] = new king(playerOne);

}

void board::displayBoard() {
	std::vector<std::shared_ptr<nana::paint::image>> tiles;

	nana::paint::image selected, highlighted, backGround, victory[2], displayCheck[2], previousAIMove;
	selected.open("Resources/selected.png");
	highlighted.open("Resources/highlighted.png");
	backGround.open("Resources/boardBackground.png");
	victory[0].open("Resources/player1Wins.png");
	victory[1].open("Resources/player2Wins.png");
	displayCheck[0].open("Resources/whiteCheck.png");
	displayCheck[1].open("Resources/blackCheck.png");
	previousAIMove.open("Resources/aiMove.png");


	nana::drawing dw(mainForm);

	dw.draw([&](nana::paint::graphics& graph){
		backGround.paste(graph, nana::point(0, 0));
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {

				tiles.emplace_back(new nana::paint::image(boardArray[y][x]->texture(x, y)));
				//King must be printed at a slightly different height
				if (boardArray[y][x]->displayOffset)
					tiles.back()->paste(graph, nana::point(squareSIZE*x + 20, squareSIZE*y + 14));
				else
					tiles.back()->paste(graph, nana::point(squareSIZE*x+20, squareSIZE*y+20));

				//Highlighted tiles need to be displayed
				if (boardArray[y][x]->getSelected())
					selected.paste(graph, nana::point(squareSIZE*x+20, squareSIZE*y+20));
				//Else if is slightly faster because a coordinate can either be selected or highlighted not both
				else if (boardArray[y][x]->getHighlighted())
					highlighted.paste(graph, nana::point(squareSIZE*x+20, squareSIZE*y+20));
				else if (boardArray[y][x]->getAIMove())
					previousAIMove.paste(graph, nana::point(squareSIZE*x + 20, squareSIZE*y + 20));


				//If one of the kings is in check or it is checkmate the player is informed
				if (checkmate) {
					victory[(turnCounter % 2 == 0)].paste(graph, nana::point(0, 0));
				} else if (check)
					displayCheck[(turnCounter % 2 != 0)].paste(graph, nana::point(0, 0));
																																													
		
			}
		}

		tiles.clear();
	});
	


	nana::API::track_window_size(mainForm, { 680, 680 }, true);
	nana::API::track_window_size(mainForm, { 680, 680 }, false);
	

	mainForm.events().click([&](const nana::arg_click& arg) {
		handleSelection(arg);
		dw.update();
	});

	mainForm.show();
	nana::exec();


}

void board::handleSelection(const nana::arg_click& arg) {
	nana::point location = arg.mouse_args->pos;

	int x = (location.x - 20) / squareSIZE;
	int y = (location.y - 20) / squareSIZE;
	int currentPlayer = (turnCounter % 2 != 0);
	tryMoves(currentPlayer);
	possibleMoveCounter = 0;


	if (y < 8 && x < 8 && !checkmate) {
		if ((!pieceSelected && boardArray[y][x]->player == currentPlayer) || (boardArray[y][x]->player == currentPlayer && !boardArray[y][x]->getHighlighted())) {
			clearSelections();
			
			boardArray[y][x]->possibleMoves(x, y, boardArray, currentPlayer);
			selectedLocation.x = x;
			selectedLocation.y = y;
			pieceSelected = true;

			//Clear possibility of player capturing enemy king
			kingThreatened(boardArray[y][x]->playerOpponent(currentPlayer));

			//Prevent player from putting themself in check
			tryMoves(currentPlayer);
			possibleMoveCounter = 0;

		}
		else if (pieceSelected) {
			if (boardArray[y][x]->getHighlighted()) {
				boardArray[selectedLocation.y][selectedLocation.x]->makeMove(selectedLocation, nana::point(x, y), boardArray);
				turnCounter++;
				clearSelections();
				check = kingThreatened(boardArray[y][x]->playerOpponent(currentPlayer));
				checkmate = checkMate(boardArray[y][x]->playerOpponent(currentPlayer));
				pieceSelected = false;

				if (aiGame && !checkmate)
					aiMove();

			}
			else
				clearSelections();
		}
	}
}


void board::clearSelections() {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			boardArray[y][x]->setHighlighted(false);
			boardArray[y][x]->setSelected(false);
		}
	}
}

void board::aiMove() {
		move bestAiMove(0, 0, 0, 0);

		std::cout << test.alphaBeta(boardArray, 3, -900, 900, 1, bestAiMove) << std::endl;
		//std::cout << "start x " << bestAiMove.getStartX() << " start y " << bestAiMove.getStartY();
		//std::cout << " x " << bestAiMove.getEndX() << " y " << bestAiMove.getEndY() << std::endl;

		boardArray[bestAiMove.getStartY()][bestAiMove.getStartX()]->makeMove(nana::point(bestAiMove.getStartX(), bestAiMove.getStartY()),
			nana::point(bestAiMove.getEndX(), bestAiMove.getEndY()), boardArray);
		std::cout << "Moves Evaluated: " << test.moveCounter << std::endl;
		std::cout << "Current board " << test.calculateBoardWeight(boardArray, 0) << std::endl;
		test.moveCounter = 0;


		turnCounter++;
		checkmate = checkMate(0);
		check = kingThreatened(0);
		if (turnCounter > 2)
			boardArray[previousLocation.y][previousLocation.x]->setAIMove(false);

		previousLocation.y = bestAiMove.getEndY();
		previousLocation.x = bestAiMove.getEndX();

		boardArray[bestAiMove.getEndY()][bestAiMove.getEndX()]->setAIMove(true);
}
bool board::kingThreatened(int player) {

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

void board::tryMoves(int currentPlayer) {
	piece* storage;

	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {

			if (boardArray[y][x]->getHighlighted()) {
				//Move the piece to the location without calling makeMove to avoid other ramifications
				storage = boardArray[y][x];
				boardArray[y][x] = boardArray[selectedLocation.y][selectedLocation.x];
				boardArray[selectedLocation.y][selectedLocation.x] = new piece;

				//The move did not take the king out of check and cannot be made
				if (kingThreatened(currentPlayer))
					storage->setHighlighted(false);
				else
					possibleMoveCounter++;

				//Return the piece to it's original location
				boardArray[selectedLocation.y][selectedLocation.x] = boardArray[y][x];
				boardArray[y][x] = storage;
			} 
		}
	}

}

//Checks if input player ID is in checkmate (ie player has lost)
bool board::checkMate(int player) {
	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {

	
			if (boardArray[y][x]->player == player) {

				//First find the possible moves for the piece
				boardArray[y][x]->possibleMoves(x, y, boardArray, player);
				selectedLocation.x = x;
				selectedLocation.y = y;

				//Then try the moves and count if there are any that break check
				tryMoves(player);

				clearSelections();
			}

			if (possibleMoveCounter > 0) {
				possibleMoveCounter = 0;
				return false;
			}
		}
	}



	return true;
}
