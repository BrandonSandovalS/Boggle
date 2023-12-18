#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    /*
     * Function: Creates a dictionary by using the load function with the dictionary text file. Initializes
     *           board to empty string and visited to 0.
     * Precondition: dictionary.txt, board, and visited must exist
     * Postcondition: Loads dict with dictionary.text and sets board to empty string and visited to 0.
     */
    Boggle();  // load "dictionary.txt" into dict

    /*
     * Function: Creates a dictionary by using the load function with the filename text file. Initializes
     *           board to empty string and visited to 0.
     * Precondition: dictionary.txt, board, and visited must exist
     * Postcondition: Loads dict with filename and sets board to empty string and visited to 0.
     */
    explicit Boggle(string filename);  // load filename into dict

    /*
     * Function: Goes through this board and the parameter and does a deep copy.
     * Precondition: board and the parameter must be set up correctly
     * Postcondition: goes through the 2-D array and copies every value of the parameter into the instance of
     *                this board.
     */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    /*
     * Function: Makes wordsFound to empty. Then iterates through the loop and calls solveboardhelper
     *           with the positions of i and j. All this to solve the boggle
     * Precondition: wordsFound and MakeEmpty need to implemented, the function needs to have been passed
     *               a bool and an ostream via the parameters and solveboardhelper needs to be implemented.
     * PostCondition: After iterating through the board and calling solveboardhelper it solves the board
     *                and prints it.
     */
    void SolveBoard(bool printBoard, ostream& output);

    /*
     * Function: Saves wordsFound into filename
     * Precondition: wordsfound and the parameter must exist
     * Postcondition: saves wordsfound into the filename
     */
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    /*
     * Function: returns dict
     * Precondition: dict must exist
     * Postcondition: returns dict
     */
    Dictionary GetDictionary();
    /*
     * Function: returns wordsFound
     * Precondition: wordsFound must exist
     * Postcondition: returns wordsFound
     */
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    /*
     * Function: Iterates through the BOARD_SIZE in a 2-D array and prints the board depending on visited
     * Precondition: visited and board must exist and be initialized
     * Postcondition: Prints a board with the appropriate spacing, apostrophe, character, and number.
     */
    void PrintBoard(ostream& output);
    /*
     * Function: Recursively calls solveboardhelper with 2 positions, step, string, bool to print the board
     *           and the ostream to print the board
     * Precondition: All the parameters must be correct and dict, visited, board, and wordsfound must exist.
     * Postcondition: After checking if positions were out of bounds, if you have not visited the position
     *                before, add the char at the position into the parameter string, then check if the word
     *                is not a prefix, then set visited in position into step and increment the step. Then
     *                check if the word is in the dictionary (word is valid) and checks if the word is in
     *                not in words found, if it is true then the word is added into words found and prints
     *                the board according to the bool parameter. Then it calls the function according to
     *                all the positions N,NE,E,SE,S,SW,W,NW, then sets visited in positions into 0.
     */
    void SolveBoardHelper(int pos1, int pos2, int step, string word, bool printBoard, ostream &output);
};

#endif //BOGGLE_BOGGLE_H
