#include "ticTacToe.h"
#include <iostream>
#include <string>

ticTacToe::ticTacToe() : winningPlayer('0'), playerMove{ 0,0,0}, aiMove{ 0,0,0 } {}

void ticTacToe::printBoard()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int ticTacToe::checkWinner()
{
    bool gameTie = true;
    winningPlayer = '0';

    //check if there is a horizontal winner
    for (int i = 0; i < 3; i++) {
        if ((equals3(board[i][0], board[i][1], board[i][2])) && ('-' != board[i][0])) {
            winningPlayer = board[i][0];
            break;
        }
    }
    //check if there is a vertical winner
    for (int i = 0; i < 3; i++) {
        if ((equals3(board[0][i], board[1][i], board[2][i])) && ('-' != board[0][i])) {
            winningPlayer = board[0][i];
            break;
        }
    }
    //check if there is a diagonal winner
    if ((equals3(board[0][0], board[1][1], board[2][2])) || (equals3(board[0][2], board[1][1], board[2][0]))) {
        if ('-' != board[1][1]) {
            winningPlayer = board[1][1];
        }
    }
    //check for a tie
    if ('0' == winningPlayer) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ('-' == board[i][j]) {//if there is an empty space, the game is not over yet
                    gameTie = false;
                    break;
                }
            }
        }
        if (true == gameTie) {//will be true if there was a tie ^
            winningPlayer = 'T';
        }
    }

    //return an integer evaluation of the position
    switch (winningPlayer) {
    case 'T':
        return TIE;
        break;
    case 'X':
        return WIN;
        break;
    case 'O':
        return LOSE;
        break;
    default:
        return NOTDONE;
    }
}

char ticTacToe::getWinner()
{
    return winningPlayer;
}

void ticTacToe::getPlayerMove()
{
    std::string move;

    while (true) {
        std::cout << "Enter your move (row# col#): ";

        //try to read two integer values from the input
        if (std::cin >> playerMove.xCoordinate >> playerMove.yCoordinate) {

            std::cout << std::endl;//formatting

            //check if the input numbers are within range
            if (playerMove.xCoordinate >= 1 && playerMove.xCoordinate <= 3 &&
                playerMove.yCoordinate >= 1 && playerMove.yCoordinate <= 3) {
                //verify that the space requested is available
                if ('-' == board[playerMove.xCoordinate-1][playerMove.yCoordinate-1]) {
                    break;
                }else {
                    std::cout << "That spot is already taken!" << std::endl;
                }
            }else {
                std::cout << "Coordinates out of range. Valid range is 1-3." << std::endl;
            }
        }else {
            std::cout << "Invalid input format. Enter your move (row# col#): " << std::endl;
            std::cin.clear();//clear the error flag
            std::cin.ignore();//clear the remaining input
        }
    }

    //update the board
    board[playerMove.xCoordinate-1][playerMove.yCoordinate-1] = 'X';

    return;
}

void ticTacToe::getAiMove() {
    
    //find the best AI move using minimax algorithm
    aiMove = miniMax(board, 8, false);

    //update the board
    board[aiMove.xCoordinate][aiMove.yCoordinate] = 'O';
}

ticTacToe::MOVE ticTacToe::miniMax(char board[3][3], int depth, bool maxing)
{
    //basic mini-max algorithm that performs a tree search and evalues all possible moves and assigns each final position a weight.
    //returns the move that results in the least favourable outcome for the player

    MOVE aiAttempt;
    aiAttempt.score = checkWinner();
    //if we are at max search depth or the game is done return position evaluation
    if (depth == 0 || ticTacToe::NOTDONE != aiAttempt.score) {
        return aiAttempt;
    }

    //this block represents the moves that the player would make (best in each position)
    if (maxing) {
        aiAttempt.score = ticTacToe::LOSE;//initialize with lowest possible score
        for (int i = 0; i < 3; i++) {//iterate through each space of the board and check if its available
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = 'X';//try a move if its available
                    MOVE tempMove = miniMax(board, depth - 1, false);//player just made a move, now let the AI make amove
                    if (tempMove.score >= aiAttempt.score) {//is the current position better for player than previous one?
                        //store the coordinates of the best move 
                        aiAttempt.score = tempMove.score;
                        aiAttempt.xCoordinate = i;
                        aiAttempt.yCoordinate = j;
                    }
                    board[i][j] = '-';//revert the change                  
                }
            }
        }
        return aiAttempt;
    }
    //this block represents the moves that the AI would make (worst for the player in each position)
    else {
        aiAttempt.score = ticTacToe::WIN;//initialize with highest possible score
        for (int i = 0; i < 3; i++) {//iterate through each space of the board and check if its available
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = 'O';//try a move if its available
                    MOVE tempMove = miniMax(board, depth - 1, true);//ai made a move, let the player make a move
                    if (tempMove.score <= aiAttempt.score) {//is the current position worse for opponent than previous one?
                        //store the coordinates of the worst move 
                        aiAttempt.score = tempMove.score;
                        aiAttempt.xCoordinate = i;
                        aiAttempt.yCoordinate = j;
                    }
                    board[i][j] = '-';//revert the change                  
                }
            }
        }
        return aiAttempt;
    }
}

bool ticTacToe::equals3(char a, char b, char c)
{
    if (a == b && b == c) {
        return true;
    }
    else {
        return false;
    }
}
