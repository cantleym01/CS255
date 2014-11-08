#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <iostream> //input & output
#include <vector> //vectors
#include <fstream> //file handling
#include <ctype.h> //tolower
#include <assert.h> //assert()
#define alphabetSize 26
#define suggestionSize 10

using namespace std; //no std::

class SpellChecker {
protected:
    //struct for the nodes of the trie
    struct node {
        string str; //the string held by the node
        string word; //if node is end of word, it will contain the word
        bool endOfWord; //is this node the end of a word?
        node* children[alphabetSize]; //list of the node's children pointers
        node* parent; //pointer to the parent node

        int getChild(string comparison) {
            for (int i = 0; i < alphabetSize; i++) {
                if (children[i] == NULL) {
                    return i; //comparison was not found
                }
                else if (children[i] -> str == comparison) {
                    return i; //match was found, so return that child
                }
            }
            assert (true == false); //should never reach point
        }//see if the child of this comparison exists
    };

public:
    SpellChecker(); //constructor
    ~SpellChecker(); //deconstructor

    //Trie functionality for controller
    void loadDictionary(string fileName); //put an entire dictionary into the Trie
    string* findWord(string suggestions[]); //take a word, and return suggestions if no match it found
    void getWord(); //ask the user for a word, and make sure it is acceptable

private:
    node* groot; //root node
    int numOfWords; //number of words
    string wordReadIn; //the user defined word to check

    //private functions controller cannot access
    void insertWord(string word); //insert a word into the Trie
};

#endif
