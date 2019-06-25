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
    if (row < boardDimension && col < boardDimension) {
        return true;
    }
    return false;
}

//Gets the intermediate board configuration
void getBoardConfig(char board [][26], int boardDimension) {
    char colour = '0', row = '0', col ='0';
    const char END_CHAR = '!';
    
    //Scan in input until user is finished
    while (colour != END_CHAR && row != END_CHAR && col != END_CHAR) {
        scanf(" %c%c%c", &colour, &row, &col);
        
        //Determine location user has specified
        int i = row - 'a';
        int j = col - 'a';
        
        //Set position on the board to specified colour, if position in bounds
        if (positionInBounds(boardDimension, i, j)) {
            board[i][j] = colour;
        }
    }
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

//Finds valid positions and prints them out
void findValidPositions(char board[][26], int boardDimension, char colour) {
    
    //Iterate through all positions on board
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            
            //Ensure position is unoccupied and position is valid
            if (board[row][col] == 'U' && checkValidPosition(row, col, colour, board, boardDimension)) {
                printf("%c%c\n", row + 'a', col + 'a');
            }
        }
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
bool makeMove(char board[][26], int boardDimension) {
    
    //Get move from player
    char colour = '0', rowChar = '0', colChar = '0';
    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &rowChar, &colChar);
    
    //Convert row and column into integer indices
    int row = rowChar - 'a';
    int col = colChar - 'a';
    
    //Ensure space is unoccupied
    if (board[row][col] != 'U') {
        return false;
    }
    
    //Count how many tiles need to be fliiped in each direction
    int numFlipNorth = searchNorth(row, col, colour, board, boardDimension);
    int numFlipNorthEast = searchNorthEast(row, col, colour, board, boardDimension);
    int numFlipEast = searchEast(row, col, colour, board, boardDimension);
    int numFlipSouthEast = searchSouthEast(row, col, colour, board, boardDimension);
    int numFlipSouth = searchSouth(row, col, colour, board, boardDimension);
    int numFlipSouthWest = searchSouthWest(row, col, colour, board, boardDimension);
    int numFlipWest = searchWest(row, col, colour, board, boardDimension);
    int numFlipNorthWest = searchNorthWest(row, col, colour, board, boardDimension);
    
    //If all of these values are 0 (sum is 0), no flips can be made, and move is invalid
    if (numFlipNorth + numFlipNorthEast + numFlipEast + numFlipSouthEast + 
        numFlipSouth + numFlipSouthWest + numFlipWest + numFlipNorthWest == 0) 
    {
        return false;
    }
    
    //At this point, moves can be made
    
    //Make the moves that can be made
    if (numFlipNorth > 0) {
        flipNorth(board, row, col, numFlipNorth, colour);
    }
    if (numFlipNorthEast > 0) {
        flipNorthEast(board, row, col, numFlipNorthEast, colour);
    }
    if (numFlipEast > 0) {
        flipEast(board, row, col, numFlipEast, colour);
    }
    if (numFlipSouthEast > 0) {
        flipSouthEast(board, row, col, numFlipSouthEast, colour);
    }
    if (numFlipSouth > 0) {
        flipSouth(board, row, col, numFlipSouth, colour);
    }
    if (numFlipSouthWest > 0) {
        flipSouthWest(board, row, col, numFlipSouthWest, colour);
    }
    if (numFlipWest > 0) {
        flipWest(board, row, col, numFlipWest, colour);
    }
    if (numFlipNorthWest > 0) {
        flipNorthWest(board, row, col, numFlipNorthWest, colour);
    }
    
    //Place player's chip at chosen position
    board[row][col] = colour;
    
    return true;
}

int main(int argc, char **argv)
{
    //Declare variables
    int boardDimension = 0;
    char board[26][26] = {{0}};
    bool validMove = false;
    
	//Get the dimensions of the board
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    
    //Set up the board
    setupBoard(board, boardDimension);
    
    //Print out board
    printBoard(board, boardDimension);
    
    //Get board configuration
    printf("Enter board configuration:\n");
    getBoardConfig(board, boardDimension);
    
    //Print out board
    printBoard(board, boardDimension);
    
    //Print out available moves for White
    printf("Available moves for W:\n");
    findValidPositions(board, boardDimension, 'W');
    
    //Print out available moves for Black
    printf("Available moves for B:\n");
    findValidPositions(board, boardDimension, 'B');
    
    //Get move from user, attempt to make it
    validMove = makeMove(board, boardDimension);
    
    //Output if move is valid
    if (validMove) {
        printf("Valid move.\n");
    }
    else {
        printf("Invalid move.\n");
    }
    
    //Print out board
    printBoard(board, boardDimension);
    
	return 0;
}
