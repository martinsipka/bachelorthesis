//
// Created by martin on 30.3.17.
//

#ifndef GRAVITYCOLLAPSE_FUNCTIONS_H
#define GRAVITYCOLLAPSE_FUNCTIONS_H

#include <cmath>
#include "../grid/grid.h"

//Basic helper functions.

class functions {

public:

    static constexpr double SIGMA = 0.3;

    static constexpr double RZERO = 0.7;

    static double beta(double x, double dphi);

    static double articleGauss(double x, double amplitude);

    static double xToR(double x);

    static double EUUR(grid &cGrid, int xIndex, int uIndex);

    static double maximumEUURUSlice(grid &cGrid, int uIndex);

    static double normalizedEUUR(double euur, double maxEUUR);

    static double dmdt(grid &cGrid, int xIndex, int uIndex);

    static double dPsidt(grid &cGrid, int xIndex, int uIndex);

    static double partialdPsidx(grid &cGrid, int xIndex, int uIndex);

};


#endif //GRAVITYCOLLAPSE_FUNCTIONS_H
