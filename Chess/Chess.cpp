// Chess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "board.h"
#include "piece.h"
#include <iostream>




int main()
{

	bool gameOver = false;

	board test;
	test.displayBoard();

	/* Function to handle selection. 
	if (selection is of type current player && there is no piece currently highlighted){
		 use function in piece class to determine number of possible moves and locations of moves (return int moves and array coords)

		 set there is a piece selected = true;
		 "selected piece coords" = current selection;
	}
	else if (there is a piece highlighted){
		if (current selection is in possible moves array){

			remove piece from "select piece coords" variable

			if (enemy piece at current selection){
				delete memory containing enemy piece
			}
			place piece at current selection
			set there is a piece selected = false;
		}
		else{
			clear possible moves array
		}
	}
	
	*/
	return 0;
}

