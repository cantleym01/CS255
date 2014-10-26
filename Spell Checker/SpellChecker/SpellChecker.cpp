#include "SpellChecker.h"

SpellChecker::SpellChecker() {
    groot = new node;
    groot -> endOfWord = false;
    numOfWords = 0;
} //constructor

SpellChecker::~SpellChecker() {} //deconstructor

void SpellChecker::loadDictionary(string fileName) {

    /**
        NOTE: the file reading assumes the dictionary is correct with no errors
        (All lower-case, no spaces, no special characters, etc.)
    */
    ifstream file;
    string currentWord;

    file.open(fileName.c_str()); //open the file

    assert(file.is_open()); //make sure file is open

    //insert all words into the Trie
    while(!file.eof()) {
        file >> currentWord;
        insertWord(groot, currentWord);
    }
} //put an entire dictionary into the Trie

void SpellChecker::insertWord(node* root, string word) {
    node* temp = root;
    int index = 0;

    //search for where to start appending new nodes, if any
    for (index; index < word.size(); index++) {
        //if the child already exists, keep going
        if (temp -> getChild(word.substr(index, 1)) != NULL) {
            temp = temp -> getChild(word.substr(index, 1));
        }
        else { //start appending
            temp = temp -> getChild(word.substr(index, 1));
            temp = new node;
            temp -> str = word.substr(index, 1);
        }
    }

    //done so, temp is the end of the word
    temp -> endOfWord = true;
    numOfWords++; //the number of words has increased
} //insert a word into the Trie

string* SpellChecker::findWord(string word, string suggestions[]) {

    return suggestions;
}//take a word, and return suggestions if no match it found
