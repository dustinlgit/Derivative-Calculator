#ifndef EVALUATE.H
#define EVALUATE.H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

vector<string> tokenize(const string& exp){
    vector<string> token_vector;
    string token_current;

    for(char c : exp){
        if(isalpha(c) || isdigit(c)) {token_current += c;}
        else{
            if(!token_current.empty()){
                token_vector.push_back(token_current);
                token_vector.clear();
            }
            token_vector.push_back(string(1, c));
        }

        if(!token_current.empty()) {token_vector.push_back(token_current);}

        return token_vector;
    }
}

#endif EVALUATE.H