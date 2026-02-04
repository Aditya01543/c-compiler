#include"parser.h"
#include<string>
#include"lexer.h"
#include<iostream>
#include"token.h"
#include<vector>
#include<fstream>

using namespace std;

vector<pair<string, TokenType>> tokensp;

int parse(const string filename){

    if(createTokens(filename) == 1){
        return 1;
    }

    ifstream tokenText("tokens.txt");
    string line, token="", tokentype="";
    bool takingToken = true;

    while(getline(tokenText, line)){
        if(takingToken){
            token = line;
        }else{
            tokentype = line;
            tokensp.push_back({token, static_cast<TokenType>(stoi(tokentype))});
            token = "";
            tokentype = "";
        }
        takingToken = !takingToken;
    }

    remove("tokens.txt");

    // for(pair<string, TokenType> p : tokensp){
    //     cout<<p.first<<" "<<p.second<<endl;
    // }

    return 0;
    
}