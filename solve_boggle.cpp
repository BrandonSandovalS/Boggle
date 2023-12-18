#include <iostream>
#include "Boggle.h"
#include "Dictionary.h"

using namespace std;

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            board[row][col] = "";
            visited[row][col] = 0;
        }
    }
}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            board[row][col] = "";
            visited[row][col] = 0;
        }
    }
}

// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            this->board[row][col] = board[row][col];
        }
    }
}

void Boggle::PrintBoard(ostream &output) {
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int let = 0; let < BOARD_SIZE; let++){
            if(visited[row][let] != 0){
                output << " '" + board[row][let] + "' ";
            }else if(visited[row][let] == 0){
                output << "  " + board[row][let] + "  ";
            }
        }
        output << "\t";
        for(int num = 0; num < BOARD_SIZE; num++){
            output << "  " + to_string(visited[row][num]) + "  ";
        }
        output << "\n";
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    wordsFound.MakeEmpty();
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            SolveBoardHelper(i, j, 0,board[i][j] , printBoard, output);
        }
    }

}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::SolveBoardHelper(int pos1, int pos2, int step, string word, bool printBoard, ostream &output) {
    if(pos1 > BOARD_SIZE || pos1 < 0 || pos2 > BOARD_SIZE || pos2 < 0 ){
        return;
    }
    if(visited[pos1][pos2] != 0){
        return;
    }
    word += board[pos1][pos2];
    if(!(dict.IsPrefix(word))){
        return;
    }

    visited[pos1][pos2] = step;
    step++;
    if(dict.IsWord(word) && !wordsFound.IsWord(word)){
        wordsFound.AddWord(word);
        if(printBoard){
            output << "Word: " << word << "\n";
            output << "Number of Words: " << to_string(step) << "\n";
            PrintBoard(output);
            output << "\n";
        } else{
            output << to_string(step) << "\t" << word << "\n";
        }
    }
    SolveBoardHelper(pos1 - 1, pos2, step,  word, printBoard, output);
    SolveBoardHelper(pos1 - 1, pos2 + 1, step,  word, printBoard, output);
    SolveBoardHelper(pos1, pos2 + 1, step,  word, printBoard, output);
    SolveBoardHelper(pos1 + 1, pos2 + 1, step,  word, printBoard, output);
    SolveBoardHelper(pos1 + 1, pos2, step,  word, printBoard, output);
    SolveBoardHelper(pos1 + 1, pos2 - 1, step,  word, printBoard, output);
    SolveBoardHelper(pos1, pos2 - 1, step,  word, printBoard, output);
    SolveBoardHelper(pos1 - 1, pos2 - 1, step,  word, printBoard, output);

    visited[pos1][pos2] = 0;

}

void GetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "Enter Board" << endl;
    cout << "-----------" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> board[i][j];
        }
    }
    cout << endl;
}

void HardCodedBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    board[0][0] = "a";
    board[0][1] = "u";
    board[0][2] = "c";
    board[0][3] = "o";

    board[1][0] = "n";
    board[1][1] = "l";
    board[1][2] = "n";
    board[1][3] = "i";

    board[2][0] = "o";
    board[2][1] = "s";
    board[2][2] = "a";
    board[2][3] = "e";

    board[3][0] = "m";
    board[3][1] = "a";
    board[3][2] = "i";
    board[3][3] = "e";
}

int main() {
    Boggle boggle;

    string board[BOARD_SIZE][BOARD_SIZE];

    HardCodedBoard(board);      // Provides a hard coded board
    //GetBoard(board);          // Gets a board from a user

    cout << boggle.GetDictionary().WordCount() << " words loaded." << endl << endl;

    boggle.SetBoard(board);

    string yesno;
    cout << "Show board? (y/n):  ";
    getline(cin, yesno);
    cout << endl;

    // Output to the screen.  Notice we pass in cout.
    boggle.SolveBoard(yesno == "y", cout);

    // Output to a file.  Notice we pass in a file.
    ofstream solveOutput;
    solveOutput.open("solve_output_basic.txt");
    boggle.SolveBoard(yesno == "y", solveOutput);
    solveOutput.close();

    // We can also save the words found this way.
    boggle.WordsFound().SaveDictionaryFile("solve_dictionary.txt");

    return 0;
}
