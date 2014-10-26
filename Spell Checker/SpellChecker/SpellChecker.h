#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
#define alphabetSize 26

using namespace std;

class SpellChecker {
protected:
    //struct for the nodes of the trie
    struct node {
        string str; //the string held by the node
        bool endOfWord; //is this node the end of a word?
        node* children[alphabetSize]; //list of the node's children pointers

        node* getChild(string comparison) {
            int index = 0;

            for (index; index < alphabetSize; index++) {
                if (children[index] != NULL) {
                    if (children[index] -> str == comparison) {
                        return children[index]; //match was found, so return that child
                    }
                }
                else {
                    //the comparison is not in the children, so return NULL
                    return children[index];
                }
            }
        }//see if the child of this comparison exists
    };
public:
    SpellChecker(); //constructor
    ~SpellChecker(); //deconstructor

    //Trie functionality for controller
    void loadDictionary(string fileName); //put an entire dictionary into the Trie
    string* findWord(string word, string suggestions[]); //take a word, and return suggestions if no match it found
private:
    node* groot; //root node
    int numOfWords; //number of words

    //private functions controller cannot access
    void insertWord(node* root, string word); //insert a word into the Trie
};

#endif
