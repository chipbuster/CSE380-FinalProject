#include<iostream>
#include<cstdlib>
#include<string>
#include<stdexcept>
#include<vector>

#include "progopt.h"
#include "datatypes.h"
#include "simple.h"
#include "dumpsolution.h"
#include "charged.h"

using namespace std;

int main(int argc, char** argv){

    // Read parameterfile name from command line OR use default value
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

    // Attempt to parse the opts
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

    //checkSanity will print messages for each error that it finds
    bool argsSane = progOptions::checkSanity(myOpts);
    if( !argsSane ){
      return 2;
    }
 
    if(myOpts.debug){
      progOptions::reportOptions(myOpts);
      cout << "Finished parsing arguments. Now running the main program." << endl;
    }

    //Declare these structures for output later
    vector<vector<double> > numericPath;// = vector<vector<double> >();
    vector<vector<double> > analyticPath;// = vector<vector<double> >();

    // SIMPLE PROBLEM
    if (myOpts.inputType == progOptions::simple){
      vector<Vec2> rawNumeric;// = vector<Vec2>();
      vector<Vec2> rawAnalytic;// = vector<Vec2>();
      Vec2 initialValues = Vec2(0.0,0.0);
 
      /* Solve with the appropriate method and collapse the solution
       * by turning it from vector-of-struct into vector-of-vector */
      if (myOpts.solType == progOptions::euler){
        rawNumeric = euler_simple_trajectory(initialValues, myOpts);
        numericPath = collapseSolution(rawNumeric);
      }
      else{  // Use a Runge-Kutta variant
        rawNumeric = gsl_simple_trajectory(initialValues, myOpts);
        numericPath = collapseSolution(rawNumeric);
      }

      /* If verification is turned on, calculate the analytical solution
       * and compare to numerical at the last timestep */  
      if(myOpts.verification){
        //Uses numeric solution as a template to generate the analytic one
        rawAnalytic = analytical_solution(rawNumeric);
        analyticPath = collapseSolution(rawAnalytic);

        double err = calcSimpleNumericalError(rawAnalytic, rawNumeric);
        cout << "=== Verification Mode Results ===" << endl;
        cout << "With h=" << myOpts.stepSize << " and " << myOpts.nsteps <<
               " steps, the error is " << err << endl;
      }
    }
    
    // CHARGED PROBLEM
    if (myOpts.inputType == progOptions::charged){
      vector<Vec6> rawNumeric;// = vector<Vec2>();
      vector<Vec6> rawAnalytic;// = vector<Vec2>();
      Vec6 initialValues = Vec6(0,0,0,20,0,2); // From PDF
 
      // Find solution path and collapse to vector-of-vectors
      rawNumeric = gsl_charged_trajectory(initialValues, myOpts);
      numericPath = collapseSolution(rawNumeric);
    }


    // DUMP SOLUTION TO FILES
    string outFilename = string("output.csv");
    if (myOpts.debug){
      cout << "Dumping output to " << outFilename << endl;
    }
    dumpSolutionPath(numericPath, outFilename);
    // If verification is enabled, dump the verification results
    if (myOpts.verification){
      string analyticFilename = string("analytic.csv");
      if (myOpts.debug){
        cout << "Dumping analytic solution to " << analyticFilename << endl;
      }
      dumpSolutionPath(analyticPath, analyticFilename);
    }
}
