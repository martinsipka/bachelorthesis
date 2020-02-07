//
// Created by martin on 30.3.17.
//

#include <fstream>
#include "functions.h"
#include "../solver/solverDICE.h"
#include "../iofiles/writers.h"

double functions::beta(double x, double dphi){

    return 2* M_PI * x * (1-x) * dphi * dphi;

}

double functions::articleGauss(double x, double amplitude) {
    if(x == 1) {
        return 0.0;
    }

    double r = xToR(x);

    return amplitude * solverDICE::power(r, 3) * exp(-solverDICE::power((r-RZERO)/SIGMA,2));

}

double functions::xToR(double x){
    return x/(1-x);
}

double functions::EUUR(grid &cGrid, int xIndex, int uIndex) {
    if(xIndex == cGrid.xSize){
        return 0.0;
    }
    gridPoint point = cGrid.getPoint(xIndex, uIndex);

    return 2*exp(2*point.beta) *dmdt(cGrid, xIndex, uIndex)
    + 8 * M_PI * (solverDICE::power(dPsidt(cGrid, xIndex, uIndex), 2) -
            exp(2*point.beta) * (1/(1-point.x) - 2*point.m/point.x) * solverDICE::power(1-point.x, 2) * dPsidt(cGrid, xIndex, uIndex) *
                    (partialdPsidx(cGrid, xIndex, uIndex) * (1-point.x) - point.value/point.x));

}

double functions::maximumEUURUSlice(grid &cGrid, int uIndex) {
    double maximum = 0.0;
    for(int xIndex = uIndex; xIndex < cGrid.xSize ; xIndex++){
        if(abs(cGrid.getPoint(xIndex, uIndex).euur) > maximum){
            maximum = abs(cGrid.getPoint(xIndex, uIndex).euur);
        }
    }
    return maximum;
}

double functions::normalizedEUUR(double euur, double maxEUUR) {
    if(maxEUUR < abs(euur)){
        throw 20;
    }
    return abs(euur) / (1 + maxEUUR);
}

double functions::dmdt(grid &cGrid, int xIndex, int uIndex){

    if(uIndex == 0){
        return 0;
        throw 20;
    }

    double mPrev = cGrid.getPoint(xIndex-1, uIndex-1).m + (cGrid.getPoint(xIndex, uIndex-1).m - cGrid.getPoint(xIndex-1, uIndex-1).m) /
                                                                (cGrid.getPoint(xIndex, uIndex-1).x - cGrid.getPoint(xIndex-1, uIndex-1).x) *
                                                                (cGrid.getPoint(xIndex, uIndex).x - cGrid.getPoint(xIndex-1, uIndex-1).x);

    double mNext = cGrid.getPoint(xIndex, uIndex+1).m + (cGrid.getPoint(xIndex+1, uIndex+1).m - cGrid.getPoint(xIndex, uIndex+1).m) /
                                                              (cGrid.getPoint(xIndex+1, uIndex+1).x - cGrid.getPoint(xIndex, uIndex+1).x) *
                                                              (cGrid.getPoint(xIndex, uIndex).x - cGrid.getPoint(xIndex, uIndex+1).x);

    return (mNext - mPrev)/
            (cGrid.getPoint(xIndex, uIndex+1).u - cGrid.getPoint(xIndex, uIndex - 1).u);

}

double functions::dPsidt(grid &cGrid, int xIndex, int uIndex){

    if(uIndex == 0){
        return 0;
        throw 20;
    }

    double psiPrev = cGrid.getPoint(xIndex-1, uIndex-1).value + (cGrid.getPoint(xIndex, uIndex-1).value - cGrid.getPoint(xIndex-1, uIndex-1).value) /
                                                                (cGrid.getPoint(xIndex, uIndex-1).x - cGrid.getPoint(xIndex-1, uIndex-1).x) *
                                                                (cGrid.getPoint(xIndex, uIndex).x - cGrid.getPoint(xIndex-1, uIndex-1).x);

    double psiNext = cGrid.getPoint(xIndex, uIndex+1).value + (cGrid.getPoint(xIndex+1, uIndex+1).value - cGrid.getPoint(xIndex, uIndex+1).value) /
                                                     (cGrid.getPoint(xIndex+1, uIndex+1).x - cGrid.getPoint(xIndex, uIndex+1).x) *
                                                     (cGrid.getPoint(xIndex, uIndex).x - cGrid.getPoint(xIndex, uIndex+1).x);


    return (psiNext - psiPrev)/
           (cGrid.getPoint(xIndex, uIndex + 1).u - cGrid.getPoint(xIndex, uIndex - 1).u);

}

double functions::partialdPsidx(grid &cGrid, int xIndex, int uIndex){
    
    if(xIndex == uIndex){
        return (cGrid.getPoint(xIndex+1, uIndex).value - cGrid.getPoint(xIndex, uIndex).value)/
               (cGrid.getPoint(xIndex+1, uIndex).x - cGrid.getPoint(xIndex, uIndex).x);
    }

    return (cGrid.getPoint(xIndex+1, uIndex).value - cGrid.getPoint(xIndex - 1, uIndex).value)/
           (cGrid.getPoint(xIndex+1, uIndex).x - cGrid.getPoint(xIndex - 1, uIndex).x);

}



