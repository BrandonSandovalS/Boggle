#include "Dictionary.h"
#include "Boggle.h"

// Your code here

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
            SolveBoardHelper(i, j, 1,"" , printBoard, output);
        }
    }

}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::SolveBoardHelper(int pos1, int pos2, int step, string word, bool printBoard, ostream &output) {
    if(pos1 >= BOARD_SIZE || pos1 < 0 || pos2 >=BOARD_SIZE || pos2 < 0 ){
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
            output << "Number of Words: " << to_string(wordsFound.WordCount()) << "\n";
            PrintBoard(output);
            output << "\n";
        } else{
            output << to_string(wordsFound.WordCount()) << "\t" << word << "\n";
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
