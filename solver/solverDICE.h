//
// Created by martin on 5.3.17.
//

#ifndef GRAVITYCOLLAPSE_SOLVERDICE_H
#define GRAVITYCOLLAPSE_SOLVERDICE_H


#include "../grid/grid.h"

class solverDICE {

public:

    static bool solve(grid &cGrid);

    static double integrateStep(grid &cGrid, int xIndex, int uIndex);

    static double power(double x, int e);

    static void checkEUUR(grid &cGrid);

};


#endif //GRAVITYCOLLAPSE_SOLVER_H
