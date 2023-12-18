#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    /*
     * Function: constructs the dictionary
     * Precondition: root and numwords must exist
     * Postcondition: sets root into new node and sets numwords into 0
     */
    Dictionary();
    ~Dictionary();  // I will not require this
    /*
     * Function: constructs the dictionary with another dict
     * Precondition: root, numwords must exist, and copyother must be implemented
     * Postcondition: sets root into new node, sets numwords into 0, and calls copyother function with the
     *                parameter.
     */
    Dictionary(const Dictionary& otherDict);    // copy constructor

    /*
     * Function: constructs the dictionary with the parameter
     * Precondition: root, numwords must exist, and loaddictionaryfile must be implemeted
     * Postcondition: sets root into new node, sets numwords into 0, and loaddictionaryfile with the
     *                parameter
     */
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    /*
     * Function: constructs the dictionary with the parameter, only if this dictionary is not equal to the
     *           parameter.
     * Precondition: copyother must be implemted and this dict is not equal to the parameter
     * Postcondition: calls copyother with the parameter and returns this.
     */
    Dictionary& operator=(const Dictionary& otherDict);

    /*
     * Function: Loads dict with the words in the filename
     * Precondition: Addword must be implemented, the filename must exist
     * Postcondition:  Checks if thhe hfile is able to open. Then while file reads the word in the parameter
     *                 it adds word into the dict using addword.
     */
    void LoadDictionaryFile(string filename);

    /*
     * Function: Is the wrapper function for the savdictionaryhelper and checks if the file is able to open.
     *           Then calls the helper function with the root, empty string, and the ofstream.
     * Precondition: The filename must exist and then savedictionary helper must be implemeted.
     * Postcondition: calls savedictioanrty helper with the root, empty string, and the ofstream.
     */
    void SaveDictionaryFile(string filename);

    /*
     * Function: This function adds words into the node.
     * Precondition: node must be set up correctly, the parameter must be a-z and lowercas.
     * Postcondition: a new node is set to root then iterates through the size of the word. It throws a
     *                dictionary error if the word is invalid and if node at the letters array corresponding
     *                to the character in the word is empter it makes a new ndoe. Then the currnode is set
     *                to the next currnode. Lastly at the end the currnode is word is set to true and
     *                increment num words by 1.
     */
    void AddWord(string word);

    /*
     * Function: Is a wrapper function to destroy helper with the purpose to make the dictionary empty
     * Precondition: root must not be nullptr and root and numwords must exist
     * Postcondition: calls destroyhelper to make the dictionary empty.
     */
    void MakeEmpty();

    /*
     * Function: Checks if the parameter is a word. Iterates through the wordsize and checks the value of
     *           letters with check at the end to see if node is a word or not.
     * Precondition: The parameter must be acceptable and the node and letters must exist
     * Postcondition: sets a new node into root then iterates through the size of the word and throws an
     *                error if the word is not valid. Then makes a check with the conversion of the char as
     *                an int and checks if the node of letters at the check is empty and if it is it makes
     *                a new node. Then it sets the new node into the new node of letters at the check
     *                After that it returns the new nodes is word, ultimately checking if the parameter is
     *                a word or not.
     */
    bool IsWord(string word);

    /*
     * Function: Checks if the parameter is a prefix. Iterates through the wordsize and checks the value of
     *           letters with check at the end to see if node is a prefix or not.
     * Precondition: The parameter must be acceptable and the node and letters must exist
     * Postcondition: sets a new node into root then iterates through the size of the word and throws an
     *                error if the word is not valid. Then makes a check with the conversion of the char as
     *                an int and if the new nodes letters at check is nullptr it returns false otherwise
     *                it sets the new node into the new nodes letter at check. Then it returns true.
     */
    bool IsPrefix(string word);

    /*
     * Function: Returns numwords
     * Precondition: numWords must exist
     * Postcondition: numWords is returned.
     */
    int WordCount();  // Returns total number of words in dictionary

private:

    /*class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
    };*/

    struct Node{
        // Your node structure here.
        // You can also use a struct if you like.
        Node* letters[NUM_CHARS];
        bool isWord;
        // It is strongly recommended you create a constructor
        // to set default values

        /*
         * Function: Is the constructor for node
         * Precondition: Node must have letters of numchars and isword
         * Postcondition: In the iteration of 0 to numchars set letters at i into nullptr then set isword
         *                into false.
         */
        Node(){
            for(int i = 0; i < NUM_CHARS; i++){
                letters[i] = nullptr;
            }
            isWord = false;
        }
    };

    Node* root;
    int numWords;


    /*
     * Function: Empties this dict, sets this dics numwords into the parameters dict numwords and calls
     *           copy helper. This is a wrapper function for copy helper.
     * Precondition: This dict must be initialized correctly, and copyhelper must be implemented
     * Postcondition: Empties the dict, copies numwords and calls copyhelper to copy the dictionaries
     */
    // This function is used by the
    // copy constructor and the assignment operator.
    void copyOther(const Dictionary& otherDict);


    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.

    /*
     * Function: A recursive function that iterates through the tree and deletes it node by node.
     * Precondition: The base cases must be correct and thistree and letters must exist.
     * Postcondition: Iterates through num chars and calls this tree letters at every i and checks when the
     *                litters at i is at nullptr then it deletes the instance of the letter until
     *                everything is deleted.
     */
    void destroyHelper(Node* thisTree);

    /*
     * Function: Is a recursive function and copies othertree and this tree.
     * Precondition: Othertree and thistree must exist and the values for the dicts must be valid
     * Postcondition: Checks if othertree is nullptr and sets thistree to null ptr and returns, then
     *                iterates through NUM_CHARS and if othertree letters is not nullptr this tree letters
     *                is a new node then sets this tree isword into othertree is word. Then calls the same
     *                function with the thistree at i and othertree at i.
     */
    void copyHelper(Node*& thisTree, Node* otherTree);

    /*
     * Function: Is a recursive function. Checks if curr is nullptr and returns if it is, checks if curr is
     *           a word and prints the current prefix, then for every num char you call the same function
     *           with the curr letters at i with the currprefix at i changed into a char with the alphabet
     *           in lowecase
     * Precondition: Curr must be implmeted well and the functions base cases must be valid
     * Postcondition: This saves the dictionary into the file by writing every word in curr into the file.
     */
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
