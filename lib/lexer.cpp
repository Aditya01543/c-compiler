#include<string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector<pair<string, string>> tokens;
string token = "";

enum tokenType{
    Identifier,
    Constant,
    Space,
    None,
    Other,
    OpenBrace
};

enum tokenType type = None;

bool isKeyword(string iden){
    if(iden == "void" || iden == "int" || iden == "return"){
        return true;
    }
    return false;
}

void clearToken(){
    if(type == Identifier){
        (isKeyword(token))?tokens.push_back({token, "k"}):tokens.push_back({token, "i"});
        token = "";
    }
    if(type == Constant){
        tokens.push_back({token, "c"});
        token = "";
    }
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

                if(type != Identifier){

                    if(type == Constant){
                        cout<<"Error : invalid identifier"<<endl;
                        return 1;
                    }
                    type = Identifier;

                }
                token += c;
                continue;
            }

            if(c >= '0' && c <= '9'){
                if(type != Constant && type != Identifier){
                    type = Constant;
                }
                token += c;
                continue;
            }

            if(c == ' ' || c == '\n'){
                if(type != Space){
                    clearToken();
                    type = Space;
                }
                continue;
            }

            if(c == '('){
                if(type != Other){
                    clearToken();
                    type = Other;
                }
                tokens.push_back({"(", "op"});
                continue;
            }

            if(c == ')'){
                if(type != Other){
                    clearToken();
                    type = Other;
                }
                tokens.push_back({")", "cp"});
                continue;
            }

            if(c == '{'){
                if(type != Other){
                    clearToken();
                    type = Other;
                }
                tokens.push_back({"{", "ob"});
                continue;
            }

            if(c == '}'){
                if(type != Other){
                    clearToken();
                    type = Other;
                }
                tokens.push_back({"}", "cb"});
                continue;
            }

            if(c == ';'){
                if(type != Other){
                    clearToken();
                    type = Other;
                }
                tokens.push_back({";", "semicolon"});
                continue;
            }
        }

    }

    for(pair<string, string> p : tokens){
        cout<<p.first<<" : "<<p.second<<endl;
    }

    return 0;
}