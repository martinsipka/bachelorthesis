//
// Created by martin on 8.4.17.
//

#ifndef GRAVITYCOLLAPSE_ONESTEPSOLVER_H
#define GRAVITYCOLLAPSE_ONESTEPSOLVER_H


class oneStepSolver {

public:

    static double solveForBeta(double x0, double x1, double beta0, double dphi);

    static double solveForMass(double x0, double x1, double m0, double dphi);

};


#endif //GRAVITYCOLLAPSE_ONESTEPSOLVER_H
