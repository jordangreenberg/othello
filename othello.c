#include <stdio.h>
#include <stdbool.h>

//Sets up the board based on dimensions given by user
void setupBoard(char board[][26], int boardDimension) {
    
    //Initialize all spots on the board as unoccupied
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            board[row][col] = 'U';
        }
    }
    
    //Initialize the four coloured spots
    int index = boardDimension / 2 - 1; //Index of top-left of centre of board
    board[index][index] = 'W'; //Top-left of centre four spots is White
    board[index][index + 1] = 'B'; //Top-right of centre four spots is Black
    board[index + 1][index] = 'B'; //Bottom-left of centre four spots is Black
    board[index + 1][index + 1] = 'W'; //Bottom-right of centre four spots is White
}

//Prints the game board
void printBoard(char board[][26], int boardDimension) {
    
    //Print out the first row
    printf("  ");
    char c = 'a';
    for (int i = 0; i < boardDimension; i++) {
        printf("%c", c);
        c++;
    }
    printf("\n");
    
    //Print out the game board
    c = 'a';
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            
            //Print the row header
            if (col == 0) {
                printf("%c ", c);
                c++;
            }
            
            //Print out letter at the index
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

//Checks to see if entered position is within bounds of board
bool positionInBounds(int boardDimension, int row, int col) {
    
    //Ensure indices are not negative
    if (row < 0 || col < 0) {
        return false;
    }
    
    if (row < boardDimension && col < boardDimension) {
        return true;
    }
    return false;
}

/**Checks if row and col is a legal position for a tile
 * "Looks" in direction specified, receives how many positions in each direction to look
 * A move has a chance to be legal if the spot being looked at is the opposite colour
 */
bool checkLegalInDirection(char board[][26], int boardDimension, int row, int col, char colour, int deltaRow, int deltaCol) {
    
    //Determine the position function should check
    int testRow = row + deltaRow;
    int testCol = col + deltaCol;
    
    //Ensure position is in bounds, if out of bounds return false
    if (!positionInBounds(boardDimension, testRow, testCol)) {
        return false;
    }
    
    //Determine the opposite colour
    char oppositeColour = '0';
    if (colour == 'W') {
        oppositeColour = 'B';
    }
    else {
        oppositeColour = 'W';
    }
    
    //Check position to see if it is occupied by the opposite colour
    //If so, this direction has a chance to be a legal move (it is legal so far)
    if (board[testRow][testCol] == oppositeColour) {
        return true;
    }
    //If position is unoccupied or the same colour, move is no longer legal
    else {
        return false;
    }
}

/**Checks to see if the final position of a travelled direction qualifies position as a valid move
 * Compares colour at this position to player's colour
 */
bool checkFinalPosition (int row, int col, char colour, int boardDimension, char board[][26]) {
    if (positionInBounds(boardDimension, row, col) && board[row][col] == colour) {
        return true;
    }
    return false;
}

//Searches in the North Direction, returns how many tiles can be flipped, zero if no move can be made
int searchNorth(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in North position
    int deltaNorth = -1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in North direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot North, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaNorth, 0)) {
        deltaNorth--;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaNorth, col, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the North East Direction, returns how many tiles can be flipped, zero if no move can be made
int searchNorthEast(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in North East position
    int deltaNorth = -1;
    int deltaEast = 1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in North East direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot North East, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaNorth, deltaEast)) {
        deltaNorth--;
        deltaEast++;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaNorth, col + deltaEast, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the East Direction, returns how many tiles can be flipped, zero if no move can be made
int searchEast(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in East position
    int deltaEast = 1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in East direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot East, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, 0, deltaEast)) {
        deltaEast++;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row, col + deltaEast, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the South East Direction, returns how many tiles can be flipped, zero if no move can be made
int searchSouthEast(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in South East position
    int deltaSouth = 1;
    int deltaEast = 1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in South East direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot South East, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaSouth, deltaEast)) {
        deltaSouth++;
        deltaEast++;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaSouth, col + deltaEast, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the South Direction, returns how many tiles can be flipped, zero if no move can be made
int searchSouth(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in South position
    int deltaSouth = 1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in South direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot South, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaSouth, 0)) {
        deltaSouth++;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaSouth, col, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the South West Direction, returns how many tiles can be flipped, zero if no move can be made
int searchSouthWest(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in South West position
    int deltaSouth = 1;
    int deltaWest = -1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in South West direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot South West, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaSouth, deltaWest)) {
        deltaSouth++;
        deltaWest--;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaSouth, col + deltaWest, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the West Direction, returns how many tiles can be flipped, zero if no move can be made
int searchWest(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in West position
    int deltaWest = -1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in West direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot West, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, 0, deltaWest)) {
        deltaWest--;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row, col + deltaWest, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Searches in the North West Direction, returns how many tiles can be flipped, zero if no move can be made
int searchNorthWest(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //Initialize change in North West position
    int deltaNorth = -1;
    int deltaWest = -1;
    
    //Track how many tiles can be flipped
    int tilesFlipped = 0;
    
    //Check in North West direction for opposite colour (meaning direction has a chance to be legal)
    //If opposite colour is found, move one more spot North West, and add to tiles flipped
    while (checkLegalInDirection(board, boardDimension, row, col, colour, deltaNorth, deltaWest)) {
        deltaNorth--;
        deltaWest--;
        tilesFlipped++;
    }
    
    //If opposite colours were found, check the final position to see if move is valid
    if (tilesFlipped > 0 && checkFinalPosition(row + deltaNorth, col + deltaWest, colour, boardDimension, board)) {
        return tilesFlipped;
    }
    else {
        return 0;
    }
}

//Flips tiles in the North direction
void flipNorth(char board[][26], int row, int col, int numFlips, char colour) {
    
    //Flip tiles in North direction
    for (int i = 1; i <= numFlips; i++) {
        board[row - i][col] = colour;
    }
}

//Flips tiles in the North East direction
void flipNorthEast(char board[][26], int row, int col, int numFlips, char colour) {
   
    //Flip tiles in North East direction
    for (int i = 1; i <= numFlips; i++) {
        board[row - i][col + i] = colour;
    }
}

//Flips tiles in the East direction
void flipEast(char board[][26], int row, int col, int numFlips, char colour) {
    
    //Flip tiles in East direction
    for (int i = 1; i <= numFlips; i++) {
        board[row][col + i] = colour;
    }
        
}

//Flips tiles in the South East direction
void flipSouthEast(char board[][26], int row, int col, int numFlips, char colour) {

    //Flip tiles in South East direction
    for (int i = 1; i <= numFlips; i++) {
        board[row + i][col + i] = colour;
    }
}

//Flips tiles in the South direction
void flipSouth(char board[][26], int row, int col, int numFlips, char colour) {

    //Flip tiles in South direction
    for (int i = 1; i <= numFlips; i++) {
        board[row + i][col] = colour;
    }
}

//Flips tiles in the South West direction
void flipSouthWest(char board[][26], int row, int col, int numFlips, char colour) {

    //Flip tiles in South West direction
    for (int i = 1; i <= numFlips; i++) {
        board[row + i][col - i] = colour;
    }
}

//Flips tiles in the West direction
void flipWest(char board[][26], int row, int col, int numFlips, char colour) {

    //Flip tiles in West direction
    for (int i = 1; i <= numFlips; i++) {
        board[row][col - i] = colour;
    }
}

//Flips tiles in the North West direction
void flipNorthWest(char board[][26], int row, int col, int numFlips, char colour) {

    //Flip tiles in North West direction
    for (int i = 1; i <= numFlips; i++) {
        board[row - i][col - i] = colour;
    }
}

//Attempts to make move specified by user
bool makeMove(char board[][26], int boardDimension, char player) {
    
    //Get move from player
    char rowChar = '0', colChar = '0';
    printf("Enter move for colour %c (RowCol): ", player);
    scanf(" %c%c", &rowChar, &colChar);
    
    //Convert row and column into integer indices
    int row = rowChar - 'a';
    int col = colChar - 'a';
    
    //Ensure space is unoccupied
    if (board[row][col] != 'U') {
        return false;
    }
    
    //Count how many tiles need to be flipped in each direction
    int numFlipNorth = searchNorth(row, col, player, board, boardDimension);
    int numFlipNorthEast = searchNorthEast(row, col, player, board, boardDimension);
    int numFlipEast = searchEast(row, col, player, board, boardDimension);
    int numFlipSouthEast = searchSouthEast(row, col, player, board, boardDimension);
    int numFlipSouth = searchSouth(row, col, player, board, boardDimension);
    int numFlipSouthWest = searchSouthWest(row, col, player, board, boardDimension);
    int numFlipWest = searchWest(row, col, player, board, boardDimension);
    int numFlipNorthWest = searchNorthWest(row, col, player, board, boardDimension);
    
    //If all of these values are 0 (sum is 0), no flips can be made, and move is invalid
    if (numFlipNorth + numFlipNorthEast + numFlipEast + numFlipSouthEast + 
        numFlipSouth + numFlipSouthWest + numFlipWest + numFlipNorthWest == 0) 
    {
        return false;
    }
    
    //At this point, moves can be made
    
    //Make the moves that can be made
    if (numFlipNorth > 0) {
        flipNorth(board, row, col, numFlipNorth, player);
    }
    if (numFlipNorthEast > 0) {
        flipNorthEast(board, row, col, numFlipNorthEast, player);
    }
    if (numFlipEast > 0) {
        flipEast(board, row, col, numFlipEast, player);
    }
    if (numFlipSouthEast > 0) {
        flipSouthEast(board, row, col, numFlipSouthEast, player);
    }
    if (numFlipSouth > 0) {
        flipSouth(board, row, col, numFlipSouth, player);
    }
    if (numFlipSouthWest > 0) {
        flipSouthWest(board, row, col, numFlipSouthWest, player);
    }
    if (numFlipWest > 0) {
        flipWest(board, row, col, numFlipWest, player);
    }
    if (numFlipNorthWest > 0) {
        flipNorthWest(board, row, col, numFlipNorthWest, player);
    }
    
    //Place player's chip at chosen position
    board[row][col] = player;
    
    return true;
}

//Checks to see if a specified position is valid for a move
bool checkValidPosition(int row, int col, char colour, char board[][26], int boardDimension) {
    
    //If there is a move to be made in any of the 8 directions, return true
    //This is represented by the search in that direction being greater than zero
    
    if (searchNorth(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchNorthEast(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchEast(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchSouthEast(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchSouth(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchSouthWest(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchWest(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    else if (searchNorthWest(row, col, colour, board, boardDimension) > 0) {
        return true;
    }
    return false;
}

//Evaluates and scores a potential move for the computer to make
int evaluatePosition(int row, int col, char colour, char board[][26], int boardDimension) {
    int score = 0;
    
    //Search in all eight directions
    score += searchNorth(row, col, colour, board, boardDimension);
    score += searchNorthEast(row, col, colour, board, boardDimension);
    score += searchEast(row, col, colour, board, boardDimension);
    score += searchSouthEast(row, col, colour, board, boardDimension);
    score += searchSouth(row, col, colour, board, boardDimension);
    score += searchSouthWest(row, col, colour, board, boardDimension);
    score += searchWest(row, col, colour, board, boardDimension);
    score += searchNorthWest(row, col, colour, board, boardDimension);
    
    return score;
}

//Count number of valid positions
int countValidPositions(char board[][26], int boardDimension, char colour) {
    int numValidPositions = 0;
    
    //Iterate through all positions on board
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            
            //Ensure position is unoccupied and position is valid
            if (board[row][col] == 'U' && checkValidPosition(row, col, colour, board, boardDimension)) {
                numValidPositions++;
            }
        }
    }
    return numValidPositions;
}

//Makes the best move for the computer
void makeComputerMove(char board[][26], int boardDimension, char computer) {
    int bestRow = 0, bestCol = 0;
    int bestScore = 0, score = 0;
    
    //Iterate through all the positions on the board
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            
            //If position is unoccupied and position is valid
            if (board[row][col] == 'U' && checkValidPosition(row, col, computer, board, boardDimension)) {
                
                //Evaluate this position
                score = evaluatePosition(row, col, computer, board, boardDimension);
                
                //If this is the best position so far, save this position
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }
    
    //At this point, a move has been chosen
    int row = bestRow;
    int col = bestCol;
    
    //Count how many tiles need to be flipped in each direction
    int numFlipNorth = searchNorth(row, col, computer, board, boardDimension);
    int numFlipNorthEast = searchNorthEast(row, col, computer, board, boardDimension);
    int numFlipEast = searchEast(row, col, computer, board, boardDimension);
    int numFlipSouthEast = searchSouthEast(row, col, computer, board, boardDimension);
    int numFlipSouth = searchSouth(row, col, computer, board, boardDimension);
    int numFlipSouthWest = searchSouthWest(row, col, computer, board, boardDimension);
    int numFlipWest = searchWest(row, col, computer, board, boardDimension);
    int numFlipNorthWest = searchNorthWest(row, col, computer, board, boardDimension);
    
    //Make the flips that can be made
    if (numFlipNorth > 0) {
        flipNorth(board, row, col, numFlipNorth, computer);
    }
    if (numFlipNorthEast > 0) {
        flipNorthEast(board, row, col, numFlipNorthEast, computer);
    }
    if (numFlipEast > 0) {
        flipEast(board, row, col, numFlipEast, computer);
    }
    if (numFlipSouthEast > 0) {
        flipSouthEast(board, row, col, numFlipSouthEast, computer);
    }
    if (numFlipSouth > 0) {
        flipSouth(board, row, col, numFlipSouth, computer);
    }
    if (numFlipSouthWest > 0) {
        flipSouthWest(board, row, col, numFlipSouthWest, computer);
    }
    if (numFlipWest > 0) {
        flipWest(board, row, col, numFlipWest, computer);
    }
    if (numFlipNorthWest > 0) {
        flipNorthWest(board, row, col, numFlipNorthWest, computer);
    }
    
    //Place computer's chip at chosen position
    board[row][col] = computer;
    
    //Output computer's move
    char rowChar = row + 'a';
    char colChar = col + 'a';
    printf("Computer places %c at %c%c.\n", computer, rowChar, colChar);
}

//Checks to see if the game board is full
bool isBoardFull(char board[][26], int boardDimension) {
    
    //Iterate through board, search for an unoccupied spot, meaning board is not full
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            if (board[row][col] == 'U') {
                return false;
            }
        }
    }
    return true;
}

//Checks to see if the game is over
bool isGameOver(char board[][26], int boardDimension, char player, char computer) {
    
    //If there are no valid moves for both player and computer, game is over
    if (countValidPositions(board, boardDimension, player) + countValidPositions(board, boardDimension, computer) == 0) {
        return true;
    }
    
    //If the board is full, game is over
    if (isBoardFull(board, boardDimension)) {
        return true;
    }
    
    return false;
}

//Determines the winner of the game
char determineWinner(char board[][26], int boardDimension) {
    int numWhite = 0, numBlack = 0;
    
    //Iterate through board and add up all white and black tiles
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            if (board[row][col] == 'W') {
                numWhite++;
            }
            else if(board[row][col] == 'B') {
                numBlack++;
            }
        }
    }
    
    //Return winning character, or 0 if a draw
    if (numWhite == numBlack) {
        return 0;
    }
    
    else if (numWhite > numBlack) {
        return 'W';
    }
    
    else {
        return 'B';
    }
}

int main(int argc, char **argv)
{
	//Declare variables
    int boardDimension = 0;
    char board[26][26] = {{0}};
    char computer = 0, player = 0;
    char turn = 'B';
    bool printNeeded = true;
    bool gameOver = false;
    char winner = 0;
    
    //Get the dimensions of the board
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    
    //Set up the board
    setupBoard(board, boardDimension);
    
    //Get colour of computer player
    printf("Computer plays (B/W): ");
    scanf(" %c", &computer);
    
    //Determine colour of player
    if (computer == 'B') {
        player = 'W';
    }
    else {
        player = 'B';
    }
    
    //Start the game loop, loop until game is over
    while (!gameOver) {
        
        //Print out board if necessary
        if (printNeeded) {
            printBoard(board, boardDimension);
            printNeeded = false;
        }
        
        //Ensure the game is not over as a result of previous move (no available moves or board is full)
        if (isGameOver(board, boardDimension, player, computer)) {
            gameOver = true;
            break;
        }
        
        //If it is the player's turn, attempt to make player move
        if (turn == player) {
            
            //Check to see that the player has an available move
            int numValidPositions = countValidPositions(board, boardDimension, player);
            
            //If there is an available move, prompt user to make one
            if (numValidPositions > 0) {
                bool validMove = makeMove(board, boardDimension, player);
            
                //If player made invalid move, end the game, declare computer as winner
                if (!validMove) {
                    printf("Invalid move.\n");
                    gameOver = true;
                    winner = computer;
                }
            
                //If the player made a valid move, switch turn to the computer, ensure board is printed
                else {
                    turn = computer;
                    printNeeded = true;
                }
            }
            
            //If there is no available move for the player, switch turn to computer
            else {
                printf("%c player has no valid move.\n", player);
                turn = computer;
            }
            
        }
        
        //If it is the computer's turn, attempt to make computer move
        else {
            
            //Check to see that the computer has an available move
            int numValidPositions = countValidPositions(board, boardDimension, computer);
            
            //If there is an available move, make it
            if (numValidPositions > 0) {
                makeComputerMove(board, boardDimension, computer);
                
                //Switch turn to player and ensure board is printed
                turn = player;
                printNeeded = true;
            }
            
            //If there is no available move for the computer, switch turn to player
            else {
                printf("%c player has no valid move.\n", computer);
                turn = player;
            }
            
        }
    }
    
    //At this point, the game is over
    
    /**Determine if player has yet to be determined
     * If so, determine the winner
     * The winner will only have been determined already at this point by an invalid player move during gameplay
     */
    if (winner == 0) {
        winner = determineWinner(board, boardDimension);
    }
    
    //Output result if not a draw
    if (winner != 0) {
        printf("%c player wins.\n", winner);
    }
    
    //Output resutl if a draw
    else {
        printf("Draw!");
    }
    
	return 0;
}
