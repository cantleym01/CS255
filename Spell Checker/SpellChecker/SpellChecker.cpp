#include "SpellChecker.h"

SpellChecker::SpellChecker() {
    groot = new node;
    groot -> endOfWord = false;
    groot -> parent = NULL;
    groot -> str = "";

    //initialize all of the children pointers to NULL
    for (int i = 0; i < alphabetSize; i++)
    {
        groot -> children.push_back(NULL);
    }

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
        insertWord(currentWord);
    }
} //put an entire dictionary into the Trie

void SpellChecker::insertWord(string word) {
    node* temp = groot;

    //search for where to start appending new nodes, if any
    for (int i = 0; i < word.size(); i++) {
        //if the child already exists, keep going
        node* child = temp -> children[temp -> getChild(word.substr(i, 1))];

        if (child != NULL) {
            temp = child;
        }
        else { //start appending
            node* parent = temp;
            child = new node;
            parent -> children[temp -> getChild(word.substr(i, 1))] = child;
            child -> str = word.substr(i, 1);
            child -> parent = parent;

            //initialize all of the children pointers to NULL
            for (int i = 0; i < alphabetSize; i++)
            {
                child -> children.push_back(NULL);
            }

            temp = child;
        }
    }

    //done so, temp is the end of the word
    temp -> endOfWord = true;
    temp -> word = word;
    numOfWords++; //the number of words has increased
} //insert a word into the Trie

string* SpellChecker::findWord(string suggestions[]) {
    node* temp = groot;
    int index = 0;
    int suggest = 0;

    //search for the word
    for (index = 0; index < wordReadIn.size(); index++) {

        //get the child
        node* child = temp -> children[temp -> getChild(wordReadIn.substr(index, 1))];

        //this character is good, keep going
        if (child != NULL) {
            temp = child;

            //check if that char was the end of a word
            if (temp -> endOfWord) {
                //now check if the words match
                if (wordReadIn == temp -> word) {

                    //empty the suggestions
                    for (int i = 0; i < suggestionSize; i++) {
                        suggestions[i] = "";
                    }

                    return suggestions; //return everything
                }
                else { //add to suggestions
                    suggestions[suggest] = temp -> word;

                    //increase suggestion index size and reset if needed
                    suggest++;
                    if (suggest == suggestionSize) {
                        suggest = 0;
                    }
                }
            }
        }
        else { //word not found, so exit to add last suggestions and return
            break;
        }
    }

    index = 0; //reset index for another use

    node* current = temp;
    temp = temp -> parent;
    //now check the words with 1 less character
    while (temp -> children[index] != NULL && index < alphabetSize)
    {
        //if the child is the end of a word, add it to suggestions
        if (temp -> children[index] -> endOfWord) {
            suggestions[suggest] = temp -> children[index] -> word;
            suggest++;
            if (suggest == suggestionSize) {
                suggest = 0;
            }
        }
        index++;//increase index as well
    }

    index = 0; //reset index for another use

    temp = current;
    //first check the words with same amount of characters (has priority)
    while (temp -> children[index] != NULL && index < alphabetSize)
    {
        //if the child is the end of a word, add it to suggestions
        if (temp -> children[index] -> endOfWord) {
            suggestions[suggest] = temp -> children[index] -> word;
            suggest++;
            if (suggest == suggestionSize) {
                suggest = 0;
            }
        }
        index++;//increase index as well
    }

    return suggestions;
}//take a word, and return suggestions if no match it found

void SpellChecker::getWord()
{
    bool badWord = false; //innocent until proven guilty
    int amountOfChars = alphabetSize;
    //lowercase and uppercase letters are the only ones allowed
    char acceptableChars[alphabetSize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                              'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    //get input
    while (true) {
        cout << "Enter a word: " << endl;
        cin >> wordReadIn;

        //if bad, input try again
        if (!cin) {
            cin.clear();
            cin.ignore (200, '\n');
            continue;
        }
        else { //input was good, but now check if it is an acceptable word

            /**
                Using a nested loop here as not much performance loss, because
                it only happens with user input, and that is very small in the scope of things
            */

            //convert the word into lowercase characters
            for (int i = 0; i < wordReadIn.size(); i++) {
                wordReadIn[i] = tolower(wordReadIn[i]);
            }

            //trace through word checking for invalid characters
            for (int i = 0; i < wordReadIn.size(); i++) {
                for (int j = 0; j < amountOfChars; j++) {
                    if (wordReadIn[i] == acceptableChars[j]) {
                        break; //char was found, go to next char
                    }

                    //if the comparison char is z and that did not match, no valid char
                    if (j == alphabetSize - 1) {
                        badWord = true;
                    }
                }
                if (badWord) { //if it was a bad word, exit loop
                    break;
                }
            }
            //check if the word was bad
            if (badWord == false) {
                break; //all was good, so exit loop
            }
            else {
                cin.clear();
                cin.ignore (200, '\n');
                badWord = false; //innocent until proven guilty
                continue;
            }
        }
    }
} //ask the user for a word, and make sure it is acceptable
