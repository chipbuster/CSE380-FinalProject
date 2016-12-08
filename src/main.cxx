#include<iostream>
#include<cstdlib>
#include<string>

#include "progopt.h"

using namespace std;

int main(int argc, char** argv){
    string optionFilename;
    if (argc == 1){
        optionFilename = "input.dat"; //If no args given, assume input.dat
    }
    else if (argc == 2){
        optionFilename = string(argv[2]); //If one arg given, use that arg
    }
    else{
        cout << "I don't know what you're trying to do. Please provide "
            << "the name of the parameter file as the only argument, or "
            << "run the program with no arguments to use \"input.dat\" "
            << "as the parameter file." << endl;
    }

}
