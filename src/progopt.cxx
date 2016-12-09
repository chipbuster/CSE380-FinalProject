#include<stdexcept>
#include<iostream>
#include<string>

#include "progopt.h"
#include "grvy.h"

using std::cerr;
using std::endl;

namespace progOptions{

  Options parseProgOptions(std::string filename){
    int inputTypeStr = -1, solTypeStr = -1, nsteps = -1;
    double stepSize;
    bool verification, debug;

    GRVY::GRVY_Input_Class iparse;

    // Parse the input from the file, using default options where appropriate
    if(! iparse.Open(filename.c_str())){
      throw std::invalid_argument("Could not open input file");
    }

    if(!iparse.Read_Var("problem",&inputTypeStr)){
      throw std::invalid_argument("Could not read required parameter \"problem\"");
    }

    if(!iparse.Read_Var("solMethod",&solTypeStr)){
      throw std::invalid_argument("Could not read required parameter \"solMethod\"");
    }

    if(!iparse.Read_Var("nsteps",&nsteps)){
      throw std::invalid_argument("Could not read required parameter \"nsteps\"");
    }

    if(!iparse.Read_Var("stepSize",&stepSize)){
      throw std::invalid_argument("Could not read required parameter \"stepSize\"");
    }

    iparse.Read_Var("verificationMode",&verification,false);

    iparse.Read_Var("debugMode",&debug,false);


    // Done parsing, now make sense of the options we've just parsed
    Options progOpts;

    // There are two valid values for inputTypeStr
    if(inputTypeStr == 0){
      progOpts.inputType = simple;
    }
    else if(inputTypeStr == 1){
      progOpts.inputType = charged;
    }
    else{
      std::cerr << "Invalid input type for \"problem\": valid args are" <<
                   " \"simple\" or \"charged\"" << std::endl;
      throw std::invalid_argument("Bad parameter value in input file"); 
    }

    // There are four valid values for solTypeStr
    if(solTypeStr == 0){
      progOpts.solType = euler;
    }
    else if(solTypeStr == 1){
      progOpts.solType = rk4;
    }
    else if(solTypeStr == 2){
      progOpts.solType = rkck;
    }
    else if(solTypeStr == 3){
      progOpts.solType = rkf45;
    }
    else{
      std::cerr << "Invalid input type for \"solMethod\": valid args are" <<
                   " \"euler\",\"rk4\",\"rkck\",\"rkf45\"" << std::endl;
      throw std::invalid_argument("Bad parameter value in input file"); 
    }

    // These are okay to use directly, since the parsing step will either
    // fail or assign default values to them.
    progOpts.stepSize = stepSize;
    progOpts.verification = verification;
    progOpts.debug = debug;
    progOpts.nsteps = nsteps;
    
    return progOpts;
  }

  // Make sure the options all make sense.
  bool checkSanity(const Options& opts){
    bool argsConsistent = true;
    if (opts.inputType == charged && opts.solType == euler){
      cerr << "Euler method not implemented for charged particle problem. " 
           << '\n' << "Check the input file and try again." << endl;
      argsConsistent = false;
    }

    if (opts.inputType == charged && opts.verification){
      cerr << "Cannot run in verification mode with charged particle problem: "
           << '\n' << "Analytical solution not prepared." << endl;
      argsConsistent = false;
    }

    if(opts.inputType == simple && opts.solType != euler && opts.solType != rk4){
      cerr << "Only euler and rk4 can be used to solve the simple problem" << endl;
      argsConsistent = false;
    }

    return argsConsistent;
  }
}

