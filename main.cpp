#include <iostream>
#include <string>
#include <cstdlib>
#include "lib/lexer.h"
#include "lib/parser.h"

using namespace std;

int main(int argc, char* argv[]) {

    string filename, argument;

    if(argc > 3)cout<<"Error : too many arguments"<<endl;
    
    if(argc < 2){
        cout<<"Error : No file specified"<<endl;
    }else{
        filename = argv[1];
        if(filename.ends_with(".h") || filename.ends_with(".c")){

            filename.erase(filename.end()-2, filename.end());
            filename += ".i";
            string cmd = "gcc -E -P ";
            cmd += argv[1];
            cmd += " -o ";
            cmd += filename;
            
            system(cmd.c_str());

            if(parse(filename) == 1){
                cout<<"Error"<<endl;
                return 1;
            }

            return 0;

        }else{
            cout<<"Error : Unsupported file type"<<endl;
        }

        if(argc == 3){
            argument = argv[2];
        }
    }

    return 0;
}
