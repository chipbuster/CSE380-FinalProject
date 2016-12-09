#include<iostream>
#include<vector>
#include<fstream>

#include "dumpsolution.h"

using namespace std;

// We have [[x1,y1,z1],[x2,y2,z2],...]. We want to reformat
// the data so that we have [x1,x2,...,y1,y2,...,z1,z2,...]
vector<double> mergeSolutionPath(vector<vector<double> > solPath){

  size_t numVars = solPath[0].size();
  size_t numSamp = solPath.size();

  vector<double> data;
  data.reserve(numVars * numSamp);
  vector<double>::iterator it = data.begin();

  for(size_t j = 0; j < numVars; j++){
    for(size_t i = 0; i < numSamp; i++){
      *it = solPath[i][j];
      it++;
    }
  }

  return data;

}

//Dump solution paths to a file, with one variable per line, space-separated
void dumpSolutionPath(vector<vector<double> > solPath, string outFilename){
  size_t numVars = solPath[0].size();
  size_t numSamp = solPath.size();

  // Get a 1D vector where all entries of the same type (e.g. all times)
  // are in one block which is numSamp wide.
  vector<double> linearized = mergeSolutionPath(solPath);
  vector<double>::iterator it = linearized.begin();

  std::ofstream dumpF(outFilename.c_str());
  
  // Iterate down the vector, putting a newline where a new variable 
  // block begins.
  for(size_t i = 0; i < numVars; i++){
    for(size_t j = 0; j < numSamp; j++){
      if(j == numSamp - 1){
        dumpF << *it;
      } else{
        dumpF << *it << ',';
      }
      *it++;
    }
    dumpF << '\n';
  }

  dumpF.close();

}
