//
// Created by martin on 9.4.17.
//

#ifndef GRAVITYCOLLAPSE_HALFSTEPCOUNTER_H
#define GRAVITYCOLLAPSE_HALFSTEPCOUNTER_H


#include "../grid/grid.h"

//Writers for convergence test.

class halfStepWriter {

public:
    static void writeHalfStep(grid &fullGrid, grid &halfGrid);

    static void writeFraction(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex);
    static void writeFractionBeta(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex);
    static void writeFractionM(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex);

    static void writeFractionHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex);
    static void writeFractionBetaHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex);
    static void writeFractionMHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex);

};


#endif //GRAVITYCOLLAPSE_HALFSTEPCOUNTER_H
