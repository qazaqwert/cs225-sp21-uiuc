/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    std::vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    std::string daWord;
    ifstream file(word_list_fname);

    if (file.is_open()) {
        while (getline(file, daWord)) {    
            if (5 == daWord.length()) {
                std::string daTemp = daWord.substr(0, 1);
                daTemp.append(daWord.substr(2, daWord.length() - 2));

                if (!d.homophones(daTemp, daWord.substr(1, daWord.length() - 1))){
                    //std::cout << "ruh roh raggy, retard" << std::endl;
                    ;
                }
                if (d.homophones(daTemp, daWord.substr(1, daWord.length() - 1)))
                    ret.push_back(std::make_tuple(daWord,
                     daWord.substr(1, daWord.length() - 1), daTemp));
            }
        }
    }
    
    return ret;
}
