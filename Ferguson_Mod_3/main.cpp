#include <iostream>
#include "ticTacToe.h"//custom class

using namespace std;

//main game loop
int main(void) {

	ticTacToe gameOne;
	bool playerTurn = true;

	//print out the board at the start of the game
	gameOne.printBoard();
	
	do
	{
		if (playerTurn) {
			gameOne.getPlayerMove();
			cout << "Player Move:" << endl;
		}else {
			gameOne.getAiMove();
			cout << "AI Move:" << endl;
		}

		//alternate player
		playerTurn = !playerTurn;

		//print out the game board after each move
		gameOne.printBoard();

	} while (!gameOne.checkWinner());//iterate until there is a winner

	//convey the result of the game!
	switch (gameOne.getWinner()) {
	case 'X':
		cout << "You won the game! Thanks for playing!";
		break;
	case 'O':
		cout << "YOU LOSE!!! *sad music* Better luck next time!";
		break;
	default:
		cout << "The game is a tie! Thanks for playing!";
	}

	return 0;
}