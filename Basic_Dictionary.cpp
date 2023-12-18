#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary() {
    root = new Node;
    numWords = 0;
}

Dictionary::Dictionary(string filename) {
    root = new Node;
    numWords = 0;
    LoadDictionaryFile(filename);
}

Dictionary::~Dictionary() {

}

Dictionary::Dictionary(const Dictionary &otherDict) {

}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream file;
    file.open(filename);
    if(!file.is_open())
        throw DictionaryError(filename + "failed to open");
    string word;
    while(file >> word){
        AddWord(word);
    }
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream file;
    file.open(filename);
    if(!file.is_open())
        throw DictionaryError(filename +"failed to open");
    SaveDictionaryHelper(root, "", file);
}

void Dictionary::AddWord(string word) {
    Node* currNode = root;
    for(int i = 0; i < word.size(); i++){
        // 97 = 'a' in int, 122 = 'z' in int
        if((int(word[i]) < 97 || int(word[i] > 122)))
            throw DictionaryError("Invalid character");

        int check = int(word[i]) - 97;
        if(currNode->letters[check] == nullptr) {
            currNode->letters[check] = new Node;
        }
        currNode = currNode->letters[check];
    }
    currNode->isWord = true;
    numWords++;
}

void Dictionary::MakeEmpty() {

}

bool Dictionary::IsWord(string word) {
    Node* currNode = root;
    for(int i = 0; i < word.size(); i++){
        if((int(word[i]) < 97 || int(word[i] > 122)))
            throw DictionaryError("Invalid character");
        int check = int(word[i]) - 97;
        currNode = currNode->letters[check];
    }
    return currNode->isWord;
}

bool Dictionary::IsPrefix(string word) {
    Node* currNode = root;
    for(int i = 0; i < word.size(); i++){
        if((int(word[i]) < 97 || int(word[i] > 122)))
            throw DictionaryError("Invalid character");
        int check = int(word[i]) - 97;
        if(currNode->letters[check] == nullptr)
            return false;
        currNode = currNode->letters[check];
    }
    return true;
}

int Dictionary::WordCount() {
    return numWords;
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    return *this;
}

Dictionary * Dictionary::copyOther(const Dictionary &otherDict) {

}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {

}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {

}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if(curr == nullptr)
        return;
    if(curr->isWord)
        outFile << currPrefix << endl;
    for(int i = 0; i < currPrefix.size(); i++){
        SaveDictionaryHelper(curr, currPrefix, outFile);
    }
}




int main() {

    Dictionary dict;
    dict.LoadDictionaryFile("dictionary.txt"); // I recommend using the small dictionary first.
    cout << dict.WordCount() << " words loaded." << endl << endl;

    // Below is some code to help you test your dictionary for Part A...
    string word;
    while (word != "!") {
        cout << "Enter string: ";
        cin >> word;

        try {
            if (dict.IsWord(word)) {
                cout << word << " is a valid word" << endl;
            } else {
                cout << word << " is NOT a valid word" << endl;
            }

            if (dict.IsPrefix(word)) {
                cout << word << " is a valid prefix" << endl;
            } else {
                cout << word << " is NOT a valid prefix" << endl;
            }
        }
        catch (DictionaryError error) {
            cout << "ERROR: " << error.Msg() << endl;
        }

        cout << endl;
    }

}
