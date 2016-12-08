#ifndef PROGOPT_H
#define PROGOPT_H

namespace progOptions{

  enum InputProblemType {simple, chargedParticle};
  enum SolveMethod {euler, rk4, rkck, rkf45};

  class options{
    InputProblemType inputType;
    SolveMethod solType;
    double stepSize;
    bool verification;
    bool debug;
  };

}

#endif
