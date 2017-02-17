#include "NgramTree.h"

#include <iostream>
#include <set>
#include <algorithm>

bool comp(string &a, string &b){
    return a.length() < b.length();
}

void NgramTree::add(string val){

    string prefix = "";
    string suffix = "";
    size_t j;
    for (j = 0; j < val.length() && val[j] != ' '; j++);
    prefix = val.substr(0, j);
    suffix = val.substr(j, val.length());

    //std::cout << "Prefix " << prefix << " Suffix \"" << suffix <<"\"\n";

    this->ngrams[prefix].push_back(suffix);
    std::sort(this->ngrams[prefix].begin(), this->ngrams[prefix].end(), comp);
}

void NgramTree::remove(string val){
    string prefix = "";
    string suffix = "";
    size_t j;
    for (j = 0; j < val.length() && val[j] != ' '; j++);
    prefix = val.substr(0, j);
    suffix = val.substr(j, val.length());

    //std::cout << "Delete " << prefix << " Suffix \"" << suffix <<"\"\n";

    for(auto it = this->ngrams[prefix].begin(); it != this->ngrams[prefix].end(); it++) {
        //std::cout << "Delete iter " << prefix << " Suffix \"" << *it <<"\"\n";
        if (*it == suffix) {
            //std::cout << "Delete deletion " << prefix << " Suffix \"" << *it <<"\"\n";
            this->ngrams[prefix].erase(it);
            return;
        }
    }
}

void NgramTree::searchInText(string text, std::vector<string> &found){
    size_t i = 0;
    string currWord = "";

    text += " ";

    std::set<string> foundSuffx;

    while (i <= text.length()) {
        if (text[i] == ' ' || i == text.length()) {
            auto it = ngrams.find(currWord);
            if(it != ngrams.end()){
                //std::cout << "FOUND NGRAM " << currWord << std::endl;
                vector<string> suffixes = it->second;
                for(int suff = 0; suff < suffixes.size(); suff++){
                    //std::cout << "Check \"" << currWord + suffixes[suff] <<"\"" << " Used " << (foundSuffx.find(currWord + suffixes[suff]) == foundSuffx.end()) << std::endl;
                    if(foundSuffx.find(currWord + suffixes[suff]) == foundSuffx.end()){
                        bool isCorrect = true;
                        int j = 0;
                        for(j = 0; j < suffixes[suff].length(); j++)
                            if(text[i + j] != suffixes[suff][j]){
                                isCorrect = false;
                                //std::cout << "Kickeddd \"" << suffixes[suff] <<"\"\n";
                                break;
                            }

                        if (text[i + j] != ' ' && (i + j) != text.length()) {
                            //std::cout << "Kicked \"" << suffixes[suff] <<"\"\n";
                            isCorrect = false;
                        }

                        if (isCorrect) {
                            foundSuffx.insert(currWord + suffixes[suff]);
                            found.push_back(currWord + suffixes[suff]);
                            //std::cout << "FOUND \"" << currWord + suffixes[suff] <<"\"\n";
                        }

                    }
                }
            }

            currWord = "";
            i++;
        }
        currWord += text[i++];
    }
}