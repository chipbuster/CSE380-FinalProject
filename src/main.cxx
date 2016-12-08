#include<iostream>
#include<cstdlib>
#include<string>
#include<stdexcept>

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
        cerr << "I don't know what you're trying to do. Please provide "
            << "the name of the parameter file as the only argument, or "
            << "run the program with no arguments to use \"input.dat\" "
            << "as the parameter file." << endl;
    }

    try{
      progOptions::Options myOpts = progOptions::parseProgOptions(optionFilename);
    }
    catch(exception& e){
      cerr << "An error occurred while trying to read the parameter file." << '\n'
           << "The error was reported as: " << '\n' << e.what() << endl;
      cerr << "Fatal, exiting... " << endl;
      return 1;
    }
}
