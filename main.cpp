/* Program Title: Lab3
 * Author: Vak Karapetian
 * Description: Given a .txt named "dictionary.txt", program will recursively search dictionary for
 *  anagrams based on an inputted word or phrase.
 * Date: 10/19/2017
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lettercount.h"
using namespace std;

typedef struct
{
    vector<string> words;
    vector<LetterCount> counts;
} dictionary; // stores dictionary's words' string and LetterCount versions

void findAnagrams(LetterCount&, dictionary&, vector<int>&);

int main()
{
    string str, fileName("dictionary.txt");
    ifstream iFile(fileName);
    dictionary d;
    vector<int> matched; // vector of matched indicies for anagram
    
    /* File check */
    if(iFile.fail())
    {
        cout << "No file of name \"" << fileName << "\" found." << endl;
        cout << "Program will now terminate." << endl;
        return 0;
    }
    
    /* Collects data from file and puts into dictionary type's vectors */
    while(getline(iFile, str))
    {
        if (!str.empty()) // makes sure the string isn't empty
        {
            d.words.push_back(str);
            d.counts.push_back(LetterCount(str.c_str()));
        }
    }
    
    iFile.close(); // file no longer need
    
    /* Grabs user inputted word/phrase */
    str.clear(); // wipes previous content of str
    
    cout << "Enter a word or phrase: ";
    getline(cin, str);
    LetterCount word(str.c_str());
    
    /* Finds anagrams */
    cout << endl << "Anagrams found: " << endl;
    findAnagrams(word, d, matched);
    
    cout << endl;

    return 0;
}

/* Function Title: findAnagrams
 * Author: Vak Karapetian
 * Description: For a given dictionary d, findAnagrams finds anagrams of a target
 *  LetterCount object that can be made with d's words. Current anagrams are stored in
 *  match and are cleared once completed.
 * Date: 10/19/2017
 */

void findAnagrams(LetterCount& target, dictionary& d, vector<int>& matched)
{
    for(int i = 0; i < d.counts.size(); i++)
    {
        if(target.totalCount() == 0) // if all parts of target subtracted then anagram found
        {
            /* Print out full found anagram */
            for(int j : matched)
            {
                cout << d.words[j] << " ";
            }
            
            cout << endl;
            
            return; // return since no anagrams will be found deeper
        }

        if(target.hasAsMany(d.counts[i])) // if the current word can be subtracted from target
        {
            /* Subtract and add to anagram */
            target.subtract(d.counts[i]);
            matched.push_back(i);
            
            findAnagrams(target, d, matched); // find any anagrams for result of subtraction
            
            /* Undo subtract and push_back operations */
            target.add(d.counts[i]);
            matched.pop_back();
        }
    }
}

