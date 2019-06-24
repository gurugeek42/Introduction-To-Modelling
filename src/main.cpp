#include <iostream>
#include <string>
#include <cmath>

#include <sim.hpp>
#include <precision.hpp>
#include <variable.hpp>
#include <critical_rayleigh_checker.hpp>

#define strVar(variable) #variable
#define OMEGA 2*M_PI*4

using namespace std;

int main(int argc, char** argv) {
  cout <<"STARTING SIMULATION\n" << endl;

  std::string constantsFile = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--constants") {
      constantsFile = argv[++i];
    }
  }

  if(constantsFile == "") {
    std::cout << "No constants file found. Aborting." << std::endl;
    return -1;
  }

  const Constants c(constantsFile);
  if(not c.isValid()) {
    cout << "ABORTING\n" << endl;
    return -1;
  }
  c.print();

  if(c.isNonlinear) {
    cout << "NONLINEAR" << endl;
    Sim simulation(c);
    simulation.runNonLinear();
  } else {
    cout << "LINEAR" << endl;
    CriticalRayleighChecker crChecker(c);
    crChecker.testCriticalRayleigh();
  }

  cout << "ENDING SIMULATION" << endl;
  return 0;
}
