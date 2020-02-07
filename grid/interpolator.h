//
// Created by martin on 30.3.17.
//

#ifndef GRAVITYCOLLAPSE_INTERPOLATOR_H
#define GRAVITYCOLLAPSE_INTERPOLATOR_H


#include "grid.h"

//Interpolation functions

class interpolator {

public:

    static double getIntegratedArea(grid &cGrid, int xIndex, int uIndex);
    //Get area by north index.
    static double getArea(grid& cGrid, int xIndex, int uIndex);

    static double integral(double x);

    static double getMiddleX(grid &cGrid, int xIndex, int uIndex);

    static double getMiddleBeta(grid& cGrid, int xIndex, int uIndex);

    static double getMiddleM(grid& cGrid, int xIndex, int uIndex);

    static double getMiddlePhi(grid& cGrid, int xIndex, int uIndex);

    static double getExtrapolatedBeta(grid& cGrid, int xIndex, int uIndex, double xNew);

    static double getExtrapolatedM(grid& cGrid, int xIndex, int uIndex, double xNew);
};


#endif //GRAVITYCOLLAPSE_INTERPOLATOR_H
