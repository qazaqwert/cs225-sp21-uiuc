/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    std::string daWord;
    ifstream daFile(filename);

    if (daFile.is_open()) {
        while (getline(daFile, daWord)) {
            //we have to make a temp because references
            //hurt my foreskin
            std::string daTemp = daWord;
            std::sort(daTemp.begin(), daTemp.end());
            dict[daTemp].push_back(daWord);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    //henlo
    for (auto & daWord : words) {
        //but who exactly was in paris?
        //references hurt peko
        std::string lessgoo = daWord;
        std::sort(lessgoo.begin(), lessgoo.end());
        dict[lessgoo].push_back(daWord);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    //henlo

    //references hurt my foreskin
    std::string foreskinRepair = word;
    std::sort(foreskinRepair.begin(), foreskinRepair.end());

    if (dict.end() == dict.find(foreskinRepair)) return std::vector<std::string>();

    return dict.at(foreskinRepair);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    //henlo
    std::vector<std::vector<std::string>> daVector;

    for (auto & hi : dict) {
        std::vector<std::string> daAnagrams = hi.second;

        if (daAnagrams.size() > 1)
            daVector.push_back(daAnagrams);
        else {
            ;
        }
    }
    
    return daVector;
}
