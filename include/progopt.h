#ifndef PROGOPT_H
#define PROGOPT_H

#include<string>

namespace progOptions{

  enum InputProblemType {simple, charged};
  enum SolveMethod {euler, rk4, rkck, rkf45};

  class Options{
   public:
    InputProblemType inputType;
    SolveMethod solType;
    double stepSize;
    bool verification;
    bool debug;
  };

  Options parseProgOptions(std::string filename);

}

#endif
