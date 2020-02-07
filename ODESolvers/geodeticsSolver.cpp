//
// Created by martin on 29.3.17.
//

#include "geodeticsSolver.h"
#include "../solver/solverDICE.h"
#include "functions.h"
#include "../grid/interpolator.h"

//Solve next u
double geodeticsSolver::solveTimestep(double x, double u0){

    return 2*x/(1-x) + u0;

}

//Solve gridpoint x coordinate
double geodeticsSolver::solvePositionOneStep(double x0, double u0, double uf, double beta, double m, int xIndex, int uIndex, grid& cGrid){

    double xPred = x0 + (uf - u0) * (-1.0/2.0) * solverDICE::power(1-x0, 2) * exp(2*beta) * (1.0 - (2.0 * m * (1-x0) / x0));

    double midBeta = (beta + interpolator::getExtrapolatedBeta(cGrid, xIndex, uIndex, xPred)) / 2;
    double midM = (m + interpolator::getExtrapolatedM(cGrid, xIndex, uIndex, xPred)) / 2;
    double midX = (xPred + x0) / 2;

    return x0 + (uf - u0) * (-1.0/2.0) * solverDICE::power(1-midX, 2) * exp(2*midBeta) * (1.0 - (2.0 * midM * (1-midX) / midX));

};

//Check if the blackhole horizon is present
bool geodeticsSolver::checkDerivative(double x, double m){

    double eps = 0.65;

    return (2*m*(1-x)/x > eps);

}