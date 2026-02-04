#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
#include"token.h"

using namespace std;

unordered_set<string> keywords = {"void", "int", "return"};

string token = "";

enum TokenType type = None;

vector<pair<string, TokenType>> tokens;

bool isKeyword(string iden){
    if(keywords.contains(iden)){
        return true;
    }
    return false;
}

void clearToken(){
    if(type == Identifier){
        (isKeyword(token))?tokens.push_back({token, Keyword}):tokens.push_back({token, Identifier});
    }
    if(type == Constant){
        tokens.push_back({token, Constant});
    }
    token = "";
}

void emitSingleCharToken(char c, TokenType t) {
    clearToken();
    tokens.push_back({string(1, c), t});
    type = None;
}

int lex(const string filename){
    ifstream inputFile(filename);
    string line;

    if(!inputFile.is_open()){
        cout<<"Error opening the file"<<endl;
        return 1;
    }

    while(getline(inputFile, line)){

        for(char c:line){

            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||  c == '_'){

                if(type == None){

                    type = Identifier;

                }
                token += c;

            }else if(c >= '0' && c <= '9'){
                if(type == Identifier){
                    token += c;
                }else if(type == None){
                    type = Constant;
                    token += c;
                }else{
                    cout<<"Error : invalid identifier"<<endl;
                    return 1;
                }

            }else if(c == ' ' || c == '\n'){
                clearToken();
            }else{

                switch(c){
                    case '(':emitSingleCharToken(c, OpenParen); break;
                    case ')':emitSingleCharToken(c, CloseBrace); break;
                    case '{':emitSingleCharToken(c, OpenBrace); break;
                    case '}':emitSingleCharToken(c, CloseBrace); break;
                    case ';':emitSingleCharToken(c, Semicolon); break;
                }
                
            }
        }

    }

    for(pair<string, TokenType> p : tokens){
        cout<<p.first<<" : "<<p.second<<endl;
    }

    return 0;
}

int createTokens(const string filename){

    if(lex(filename) == 1){
        return 1;
    }

    ofstream outputFile("tokens.txt");

    if(!outputFile.is_open()){
        cout<<"Error opening tokens.txt"<<endl;
    }

    // for(pair<string, TokenType> p : tokens){
    //     outputFile << p.first << endl << p.second << endl;
    // }

    outputFile.close();

    tokens.clear();

    return 0;
    
}