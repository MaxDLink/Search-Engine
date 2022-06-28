//
// Created by Max Link on 6/26/22.
//

#include "QueryParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "stemmer.h"
#include "vector"
#include "sstream"

using namespace std;

QueryParser::QueryParser(string &query, set<string> stopWords) {
    //lowercase & remove capitals
    istringstream queryAsStream(query); //todo - either leave this or change query to istringstream later
    string word = query;
    string lowerWord;
// todo parse the queries
    // v wordList, isAnd = false
    // v personList, isAnd
    // v orgList, isAnd
    // v notWordList, isAnd

    //string query
    //v currWl = wordList
    vector<string> currWl = wordList;
    string mode = "word"; //mode starts off as word to take in general words
    string token;
    //string mode; ///todo - set equal to word at first and then change to person mode or org mode accordingly
    char feed[50];
    while (queryAsStream >> token) {///todo - take token in by space with istream or get line
        if (token == "PERSON") {//todo - currWL changes between personList, orgList, & wordList during parsing
            currWl = personList; //todo figure out what currWl should be set to
            mode = "person"; //detected person keyword so set mode to person
        } else if (token == "ORG") {
            currWl = orgList; //todo figure out what orgList should be set to
            mode = "org";
        } else if (token == "AND") {
            /// currWl.isAnd = true;
            //todo - what should this else if do?
            wordListAnd = true; //detected AND keyword so set wordListAnd == true. if false means that an OR was detected
        } else if (mode == "word") {
            currWl = wordList; //todo - permanently store words into wordList
            //lower & replace punctuation with blanks
            std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               c = std::tolower(c);
                               if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
                                   return c;
                               } else {
                                   return (unsigned char) ' ';
                               }
                           });
            //put words into current word list
            currWl.push_back(token);
        } else if (mode == "person" || mode == "org") {
            //lowercase & return token //todo - double check that person's & org's will never have special punctuation/capitalization
            std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               c = std::tolower(c);
                               return c;
                           });
            //add token to current word list
            currWl.push_back(token);
        }
    }

    ///lowercase junk
// save for lower case, no punct for search word list (not person org)
// only for terms (not person and org)
//    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
//                   [](unsigned char c) {
//                       c = tolower(c);
//                       if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
//                           return c;
//                       } else {
//                           return (unsigned char) ' ';
//                       }
//                   });

    for (int i = 0; i < word.size(); i++) {//todo - check lower casing for correct words being recorded
        //if(tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' || tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9'){//lowercases words
        if (tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' ||
            tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9') {
            lowerWord += tolower(word.at(i));
        } else {//continues if punctuation
            continue;
        }
    }

    //removes punctuation from string
    for (int i = 0; i < word.size(); i++) {
        if (ispunct(word.at(i))) {//todo - change is punct to not use .erase
            word = word.erase(i, 1); //erases any punctuation from word
        }
    }

    //if current word is not a stop word then stem & pushback to query vector
    if (!stopWords.count(lowerWord)) {
        Porter2Stemmer::stem(lowerWord);
        Porter2Stemmer::trim(lowerWord);
        // todo remove bypass when parsing wordList.push_back(lowerWord);
    }
}

vector<string> QueryParser::getWordList() {
    // todo remove stub in data
    wordList.push_back("year"); // 1 5 6 9
    wordList.push_back("year"); // 1 5 6 9
    wordList.push_back("1"); // 2 7
    //
    return wordList;
}

vector<string> QueryParser::getPersonList() {
    // todo remove stub in data
    personList.push_back("hoge");
    //
    return personList;
}

vector<string> QueryParser::getOrgList() {
    // todo remove stub in data
    // orgList.push_back("hoge");
    //
    return orgList;
}

vector<string> QueryParser::getNotWordList() {
    // todo remove stub in data
    // notWordList.push_back("notThisWord");
    //
    return notWordList;
}

bool QueryParser::isWordListAnd() {
    return true; // todo - take out & use dynamic wordListAnd bool instead
    return wordListAnd;
}

bool QueryParser::isPersonListAnd() {
    return personListAnd;
}

bool QueryParser::isOrgListAnd() {
    return orgListAnd;
}

bool QueryParser::isNotWordListAnd() {
    return notWordListAnd;
}
