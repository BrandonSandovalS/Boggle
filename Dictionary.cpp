#include "Dictionary.h"

// Your code here
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
    root = new Node;
    numWords = 0;
    copyOther(otherDict);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if(this != &otherDict)
        copyOther(otherDict);
    return *this;
}


void Dictionary::copyOther(const Dictionary &otherDict) {
    this->MakeEmpty();
    this->numWords = otherDict.numWords;
    copyHelper(this->root, otherDict.root);
}


void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if(otherTree == nullptr){
        thisTree = nullptr;
        return;
    }
    for(int i = 0; i < NUM_CHARS; i++){
        if(otherTree->letters[i] != nullptr){
            thisTree->letters[i] = new Node;
        }
        thisTree->isWord = otherTree->isWord;
        copyHelper(thisTree->letters[i], otherTree->letters[i]);
    }

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
        throw DictionaryError(filename + "failed to open");
    SaveDictionaryHelper(root, "", file);
}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr) {
        return;
    }
    if(curr->isWord)
        outFile << currPrefix << std::endl;
    for(int i = 0; i < NUM_CHARS; i++){
        SaveDictionaryHelper(curr->letters[i], currPrefix + char (i + 97), outFile);
    }
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
    if(root == nullptr){
        numWords = 0;
        return;
    }
    destroyHelper(root);
    root = new Node;
    numWords = 0;
}
void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree == nullptr){
        return;
    }
    for(int i = 0; i < NUM_CHARS; i++){
        destroyHelper(thisTree->letters[i]);
    }
    delete thisTree;
}

bool Dictionary::IsWord(string word) {
    Node* currNode = root;
    for(int i = 0; i < word.size(); i++){
        if((int(word[i]) < 97 || int(word[i] > 122)))
            throw DictionaryError("Invalid character");
        int check = int(word[i]) - 97;
        if(currNode->letters[check] == nullptr) {
            currNode->letters[check] = new Node;
        }
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
