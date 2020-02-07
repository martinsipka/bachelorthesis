//
// Created by martin on 8.4.17.
//

#include "oneStepSolver.h"
#include "functions.h"

//Solve hypersurface equation for beta.
double oneStepSolver::solveForBeta(double x0, double x1, double beta0, double dphi) {

    return beta0 + functions::beta((x1 + x0)/2, dphi) * (x1 - x0);

}

//Solve hypersurface equation for mass.
double oneStepSolver::solveForMass(double x0, double x1, double m0, double dphi) {

    double deltaX = x1 - x0;
    double midX = (x1 + x0) / 2;

    return (m0 + deltaX * dphi * dphi * 2 * M_PI * midX * (midX - (1 - midX) * m0)) /
            (1 + 2 * M_PI  * (1 - midX) * midX * deltaX * dphi * dphi);

}
