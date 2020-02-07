//
// Created by martin on 30.3.17.
//

#include "interpolator.h"

double interpolator::getIntegratedArea(grid &cGrid, int xIndex, int uIndex){
    double startX = (cGrid.getPoint(xIndex-1, uIndex).x + cGrid.getPoint(xIndex-1, uIndex - 1).x) / 2;
    double endX = (cGrid.getPoint(xIndex, uIndex).x + cGrid.getPoint(xIndex, uIndex - 1).x) / 2;

    //return (integral(endX) - integral(startX)) * (cGrid.getPoint(xIndex, uIndex).u - cGrid.getPoint(xIndex, uIndex - 1).u);
    double x = getMiddleX(cGrid, xIndex, uIndex);
    return getArea(cGrid, xIndex, uIndex) * (1-x)/x/x/x;
}

double interpolator::integral(double x){
    return 1/x - 1/2/x/x;
}

double interpolator::getArea(grid &cGrid, int xIndex, int uIndex) {

    return (cGrid.getPoint(xIndex, uIndex).x - cGrid.getPoint(xIndex-1, uIndex).x + cGrid.getPoint(xIndex, uIndex-1).x
     - cGrid.getPoint(xIndex-1, uIndex-1).x) * (cGrid.getPoint(xIndex, uIndex).u - cGrid.getPoint(xIndex, uIndex - 1).u) / 2;
}

double interpolator::getMiddleX(grid &cGrid, int xIndex, int uIndex){
    return (cGrid.getPoint(xIndex-1, uIndex).x + cGrid.getPoint(xIndex-1, uIndex - 1).x
            + cGrid.getPoint(xIndex, uIndex).x + cGrid.getPoint(xIndex, uIndex - 1).x) / 4;
}

double interpolator::getMiddleBeta(grid &cGrid, int xIndex, int uIndex) {

    return (cGrid.getPoint(xIndex-1, uIndex).beta + cGrid.getPoint(xIndex, uIndex-1).beta) / 2;

}

double interpolator::getMiddleM(grid &cGrid, int xIndex, int uIndex) {

    return (cGrid.getPoint(xIndex-1, uIndex).m + cGrid.getPoint(xIndex, uIndex-1).m) / 2;
}

double interpolator::getMiddlePhi(grid &cGrid, int xIndex, int uIndex) {

    return (cGrid.getPoint(xIndex-1, uIndex).value + cGrid.getPoint(xIndex, uIndex-1).value) / 2;
}

double interpolator::getExtrapolatedBeta(grid &cGrid, int xIndex, int uIndex, double xNew) {

    if(xIndex == uIndex+1){
        return 0;
    }

    return cGrid.getPoint(xIndex-1, uIndex).beta + (cGrid.getPoint(xIndex-1, uIndex).beta - cGrid.getPoint(xIndex-2, uIndex).beta) /
                                                           (cGrid.getPoint(xIndex-1, uIndex).x - cGrid.getPoint(xIndex-2, uIndex).x) *
                                                           (xNew - cGrid.getPoint(xIndex-1, uIndex).x) ;

}

double interpolator::getExtrapolatedM(grid &cGrid, int xIndex, int uIndex, double xNew) {

    if(xIndex == uIndex+1){
        return 0;
    }

    return cGrid.getPoint(xIndex-1, uIndex).m + (cGrid.getPoint(xIndex-1, uIndex).m - cGrid.getPoint(xIndex-2, uIndex).m) /
                                                   (cGrid.getPoint(xIndex-1, uIndex).x - cGrid.getPoint(xIndex-2, uIndex).x) *
                                                   (xNew - cGrid.getPoint(xIndex-1, uIndex).x) ;

}