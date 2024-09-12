#pragma once

class ticTacToe {
public:
    ticTacToe();

    //prints out the board to the console
    void printBoard();

    //returns the current position evaluation based on the score enum below 
    int checkWinner();

    //returns the winner if there is one
    char getWinner();

    //used to get a valid player move inputs
    void getPlayerMove();

    //used to get an AI move. Uses basic minimax
    void getAiMove();


private:

    //a structure to hold a player move or an ai move
    struct MOVE {
        int xCoordinate;
        int yCoordinate;
        int score;
    };
    //holds the most recent player move
    MOVE playerMove;
    //holds the most recent AI move
    MOVE aiMove;

    //a variable to hold the player who wins, or a character representing a tie
    char winningPlayer;

    //used to quantify a positional evaluation
    enum SCORE {
        NOTDONE,
        LOSE,
        TIE,
        WIN,
    };

    //the game board (blank)
    char board[3][3] = { {'-','-','-'},
                         {'-','-','-'},
                         {'-','-','-'}
    };

    //returns the coordinates of the best move in the position
    MOVE miniMax(char board[3][3], int depth, bool maxing);

    //a function to simplify the checkWinner function. Compares 3 chars and returns true if they are equal
    bool equals3(char a, char b, char c);

};
