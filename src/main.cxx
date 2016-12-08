#include<iostream>
#include<cstdlib>
#include<string>
#include<stdexcept>
#include<vector>

#include "progopt.h"
#include "datatypes.h"
#include "euler.h"
#include "dumpsolution.h"

using namespace std;

int main(int argc, char** argv){

    // ARGUMENT SHENANIGANS

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

    progOptions::Options myOpts;
    try{
      myOpts = progOptions::parseProgOptions(optionFilename);
    }
    catch(exception& e){
      cerr << "An error occurred while trying to read the parameter file." << '\n'
           << "The error was reported as: " << '\n' << e.what() << endl;
      cerr << "Fatal, exiting... " << endl;
      return 1;
    }

    if(myOpts.debug){
      cout << "Finished parsing arguments. Now running the main program." << endl;
    }

    //Default return types are wrapped vectors of vectors of doubles. 
    //Store the unwrapped data here for output processing later.
    vector<vector<double> > solutionPath = vector<vector<double > >(myOpts.nsteps);

    // SIMPLE PROBLEM
    if (myOpts.inputType == progOptions::simple){
      if (myOpts.solType == progOptions::euler){
        // Find the solution path
        Vec2 initialValues = Vec2(0.0,0.0);
        vector<Vec2> sol = euler_simple_trajectory(initialValues, myOpts);
        
        //Copy the solution into solutionPath
        for(int j = 0; j < myOpts.nsteps; j++){
          solutionPath[j] = sol[j].toVector();
        }
      }
    }



    // DUMP SOLUTION TO FILES
    string outFilename = string("output.csv");
    if (myOpts.debug){
      cout << "Dumping output to " << outFilename << endl;
    }
    dumpSolutionPath(solutionPath, string("output.csv"));
}
