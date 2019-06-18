/*
  MIT License

  Copyright (c) 2019 Matt Forster

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <vector>
#include <iostream>

#include "common.h"
#include "godunov.h"
#include "variables.h"
#include "test.h"

int main()
{
  std::cout << "Euler1D" << std::endl;
  std::cout << "Copyright (c) 2019 Matt Forster" << std::endl;
  std::cout << "MIT License see https://github.com/mjfcfd/Euler1D/blob/master/LICENSE for details\n" << std::endl;

  double gamma = 1.4;
  // double pRef  = 1013250;

  // state(double r, double u, double v, double w, double p, double gamma, double p_inf)
  state lState(1.0, 0.0, 0.0, 0.0, 1.0, gamma, 0.0);
  state rState(0.125  , 0.0, 0.0, 0.0, 0.1 , gamma, 0.0);

  double nM = 21;    // domain size
  double pD = 0.5;  // diaphragm position percentage
  int nD = 1;        // number of diaphragms (i think)

  int    bcL   = 0;   // left boundary condition (0 for transitive, 1 for reflexive)
  int    bcR   = 0;   // right boundary condition (0 for transitive, 1 for reflexive)
  double CFL   = 0.25;
  double dx    = 0.05;
  double rTime = 0.2;

  // initial_vector(state C0, state C1, state C2, state C3, double x0, double x1, double x2, double M, int nInt)
  state emptyState;
  std::vector<state> initVec = initial_vector(lState,rState,emptyState,emptyState,pD,0,0,nM,nD);

  std::vector<double> inPres = density(initVec);
  std::cout << "initial density" << std::endl;
  for (size_t i=0; i<inPres.size(); i++)
    std::cout << " " << inPres[i];

  std::cout << "\n" << std::endl;

  // godunov(const std::vector<state> & X, int BCL, int BCR, double dx, double C, double t)
  std::vector<state> result = godunov(initVec, bcL, bcR, dx, CFL, rTime);

  std::vector<double> fnPres = density(result);
  std::cout << "final density" << std::endl;
  for (size_t i=0; i<fnPres.size(); i++)
    std::cout << " " << fnPres[i];

  std::cout << "\n" << std::endl;

  return 0;
}
