#include <iostream>
#include "SpellChecker.h"

using namespace std;

int main()
{
    SpellChecker spellCheck;

    spellCheck.loadDictionary("dictionary.txt");

    spellCheck.getWord();

    string suggestions[suggestionSize];
    string* retSuggestions = NULL;
    retSuggestions = spellCheck.findWord(suggestions);

    //if returned suggestions is "", then the word matches
    if (retSuggestions[0] == "") {
        cout << "That word was in the dictionary" << endl;
    }
    else {
        cout << "That word was not in the dictionary" << endl <<
        "Here are some suggestions:" << endl;

        for (int i = 0; i < suggestionSize; i++) {
            cout << retSuggestions[i] << endl;
        }
    }
}
