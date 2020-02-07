//
// Created by martin on 29.3.17.
//

#ifndef GRAVITYCOLLAPSE_GEODETICSSOLVER_H
#define GRAVITYCOLLAPSE_GEODETICSSOLVER_H


#include "../grid/grid.h"

class geodeticsSolver {

public:

    static double solveTimestep(double x, double u0);

    static double solvePositionOneStep(double x0, double u0, double uf, double beta, double m, int xIndex, int uIndex, grid& cGrid);

    static bool checkDerivative(double x, double m);

};


#endif //GRAVITYCOLLAPSE_GEODETICSSOLVER_H
