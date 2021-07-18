/* pegJump.cpp

   Author: Mallika Patil and Luis Nunez
   Program: #3, Peg Jump
   CS 141, Spring 2019
 
   Description:
          This program represents a peg jumping puzzle  A
        move is made by a peg jumping over another peg into an empty
        spot, where the jumped peg is then removed from the board. The
        game ends when there are no more valid moves to make. The object
        is to eliminate as many pegs as possible.
				
		Sample output:
		
			Welcome to the peg jump puzzle! 
			Enter '-' to exit, or '+' for instructions. 

							A B C         
							D E F         
					G H I J K L M     
					N O P * Q R S     
					T U V W X Y Z     
							1 2 3         
							4 5 6         

			1. Enter the peg to move: +

			Welcome to the peg jump puzzle. The board starts out with a 
			single blank position, represented by the '*'.  To make a 
			move, select the letter of a peg.  A peg must be able to 
			jump over an adjacent peg into a blank position for a move 
			to be valid.  The jumped peg is then removed from the board. 
			The game is over when there are no valid moves left. At any 
			point enter '-' to exit, or '+' for instructions. 

			1. Enter the peg to move: E

							A B C         
							D * F         
					G H I * K L M     
					N O P E Q R S     
					T U V W X Y Z     
							1 2 3         
							4 5 6         

			2. Enter the peg to move: w

							A B C         
							D * F         
					G H I W K L M     
					N O P * Q R S     
					T U V * X Y Z     
							1 2 3         
							4 5 6         

			3. Enter the peg to move: 5

							A B C         
							D * F         
					G H I W K L M     
					N O P * Q R S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			4. Enter the peg to move: 2
			*** Invalid move, please retry. *** 
			4. Enter the peg to move: r

							A B C         
							D * F         
					G H I W K L M     
					N O P R * * S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			5. Enter the peg to move: R

							* * *         
							* 1 *         
					* * * * * * *     
					* * * + * * *     
					* * * * * * *     
							* 2 *         
							* * *         

			There is more than one possible move.  Which move do you want? 1

							A B C         
							D R F         
					G H I * K L M     
					N O P * * * S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			6. Enter the peg to move: -

			Exiting...

			27 pieces remaining. Ouch!
 */

#include <iostream>
#include <cctype>     // For toupper()
using namespace std;


//-------------------------------------------------------------------------------------
// Function for displaying instructions
void displayInstructions()
{
    cout << endl
         << "Welcome to the peg jump puzzle. The board starts out with a \n"
         << "single blank position, represented by the '*'.  To make a \n"
         << "move, select the letter of a peg.  A peg must be able to \n"
         << "jump over an adjacent peg into a blank position for a move \n"
         << "to be valid.  The jumped peg is then removed from the board. \n"
         << "The game is over when there are no valid moves left. At any \n"
         << "point enter '-' to exit, or '+' for instructions. \n"
         << endl;
}

// Function for displaying board using board array 
void displayBoard(char board[])
{
    int index = 0; 
    for(index = 11; index < 99; index++){
        if(board[index] == '#'){   // Displays space if #
            cout << "  ";
            if(((index+1) % 11) == 0){   // Inserts endl if character is a # and the index+1 is divisible by 11
                cout << endl; 
            } 
            continue;
        }
        cout << board[index] << ' '; 
    }
    cout << endl; 
}

// Function that returns index of a character 
int findIndex(const char board[], char input) 
{
    for(int i=0; i<121; i++){
        if(board[i] == input){ 
          return i; 
        }
    }
}

// Function for performing valid check 
bool isValid(char board[], int sourceIndex, int offset)
{
    bool value = false; 
    char destPiece = board[sourceIndex + offset];        // Stores character at destination 
    char pieceOneAway = board[sourceIndex+(offset/2)];   // Stores character one row or column away 
    if((destPiece == '*') &&      
       (destPiece != '#') &&     
       (pieceOneAway != '*')){    
        value = true; 
    }
    return value; 
}

// Function to return num of possible moves 
int numOfMoves(char board[], int offsetArray[], int sourceIndex, int& offsetNum)    
{
    int movesPossible = 0;
    int index;    // Index in offsetArray
    // Check all possible moves by looping through offset array
    for(index = 0; index < 4; index++){     
        int offset = offsetArray[index];    // Distance between the user's character and the four possible spaces
        if(isValid(board, sourceIndex, offset)){    // Check if valid  
            movesPossible++;
            offsetNum = offset;       // Stores offset number for valid move, used for one valid move
        }
    }
    return movesPossible;
}

// Function for making a move
void makeMove(char board[], int index, char character, int offsetNum)
{
    board[index+offsetNum] = character;
    board[index+(offsetNum/2)] = '*';
    board[index] = '*';
}

// Function for displaying options 
void displayAndUpdateOptions(char board[], int offsetArray[], int sourceIndex, char pieceUserMoves) 
{
    // Create new array for displaying options, and then ask for user choice 
    char newBoard[122];
    for(int i=0; i<122; i++){
        newBoard[i] = board[i];
        if(board[i] != '#'){
            newBoard[i] = '*';
        }
    }
    char temp = '1';
    newBoard[sourceIndex] = '+';    // Set + at the position of the user's move
    // Loop for displaying possible options for user
    for(int i=0; i<4; i++){  
        int offset = offsetArray[i];
        if(isValid(board, sourceIndex, offset)){    // Check if valid  
                newBoard[sourceIndex+offset] = temp;
                ++temp;
        }
    }
    // Display board with numbered options
    displayBoard(newBoard); 
    // Get user's choice for moving 
    char userNum = ' ';    // Initialized for user's move of choice
    cout << "There is more than one possible move. Which move do you want? ";
    cin >> userNum;                                       
    int indexOfUserNum = findIndex(newBoard, userNum);    // Find index of user's move choice   
    int offsetNum = indexOfUserNum - sourceIndex;    // Distance between user's choice and user's piece
    makeMove(board, sourceIndex, pieceUserMoves, offsetNum);
}

// Function for counting game board
int gameEndCondition(char board[], int offsetArray[], int offset, int& numPieces)
{   
    int moves = 0;    // Counts number of possible total moves
    numPieces = 0; 
    for(int i=0; i< 121; i++){
        if(((board[i]!='*') && (board[i]!='#'))){
            numPieces++;    // Counts number of remaining pieces
            moves += numOfMoves(board, offsetArray, i, offset); 
        }
    }
    return moves; 
}
//-------------------------------------------------------------------------------------

// Main function 
int main()
{
    //Variable declarations
    int moveCounter = 1; 
    char pieceUserMoves = ' '; 
    int offsetNum = 0; 
    int numPieces; 
    int offsetArray[4] = {-22,-2, 2, 22}; // Holds the distances between a piece of interest and a space one can move to
    char board[] = {
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','A','B','C','#','#','#','#',
            '#','#','#','#','D','E','F','#','#','#','#',
            '#','#','G','H','I','J','K','L','M','#','#',
            '#','#','N','O','P','*','Q','R','S','#','#',
            '#','#','T','U','V','W','X','Y','Z','#','#',
            '#','#','#','#','1','2','3','#','#','#','#',
            '#','#','#','#','4','5','6','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#'
          };
    
    // Display main message 
    cout << "Welcome to the peg jump puzzle! \n"
         << "Enter '-' to exit, or '+' for instructions. \n";
    displayBoard(board);
    
    // Main loop to play the game
    while(gameEndCondition(board, offsetArray, offsetNum, numPieces)){   // Loop until no possible moves remain
      
        // Prompt for and get move
				cout << moveCounter << ". Enter the peg to move: "; 
        cin >> pieceUserMoves;
        pieceUserMoves = toupper(pieceUserMoves);
      
        // Check for '-' to exit, and '+' for displaying instructions
				if(pieceUserMoves == '+'){
            displayInstructions();
            continue; 
        }
        else if(pieceUserMoves == '-'){
            cout << endl; 
            cout << "Exiting..." << endl; 
            cout << endl; 
            break; 
        }
  
        // Make move
        else{
            // Find index of piece user wants to move and calculate possible moves
            int indexOfUser = findIndex(board, pieceUserMoves);
            int posMoves = numOfMoves(board, offsetArray, indexOfUser, offsetNum);
            // Invalid of no. of moves
            if(posMoves == 0){ 
                cout << "*** Invalid move, please retry. ***" << endl; 
                continue; 
            }
            // If only one possible move, set the appropriate spaces to certain characters
            else if(posMoves == 1){                 
                makeMove(board, indexOfUser, pieceUserMoves, offsetNum);
            }
            // If more than one possible move, call function to display and update user choice
            else{
                displayAndUpdateOptions(board, offsetArray, indexOfUser, pieceUserMoves);    
            }
        }
				// Increment move number and display the board
				displayBoard(board);
				moveCounter++;
    }
  
    // Display appropriate message depending on number of remaining pegs
    cout << numPieces << " pieces remaining.";   // Outputs the number of remaining pieces
    if(numPieces >= 5){                            
        cout << " Ouch!";
    }
    else if(numPieces == 4){     
        cout << " Needs Improvement."; 
    }
    else if(numPieces == 3){     
        cout << " OK."; 
    }
    else if(numPieces == 2){     
        cout << " Good!"; 
    }
    else if(numPieces == 1){     
        cout << " Excellent!"; 
    }
    return 0;
}//end main()

