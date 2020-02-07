//
// Created by martin on 5.3.17.
//

#include <fstream>
#include "grid.h"
#include "../ODESolvers/oneStepSolver.h"
#include "../ODESolvers/functions.h"

grid::grid(){
    xSize = DEFAULT_X_SIZE;
    uSize = DEFAULT_U_SIZE;
    gridPoints = new gridPoint[xSize*(xSize+1)/2];
}

grid::grid(int xS, int uS){
    xSize = xS;
    uSize = uS;
    gridPoints = new gridPoint[xSize*(xSize+1)/2];
}

void grid::createGrid(){
//Initialize in case of arbitrary length
    for(int i = 0; i < uSize; i++){
        for(int j = i; j < xSize; j++){

            //otazka ako rozlozit gridpointy
            if(i <= j){
                gridPoints[getIndex(j, i)].x = (double) (j-i)/xSize;
                gridPoints[getIndex(j, i)].u = -1;
            } else {
                gridPoints[getIndex(j, i)].x = -1;
            }
            gridPoints[getIndex(j, i)].value = 0;
            gridPoints[getIndex(j, i)].xIndex = j;
            gridPoints[getIndex(j, i)].uIndex = i;
        }
    }

}

int grid::getIndex(int xIndex, int uIndex) {
    if(uIndex > xIndex){
        cout << "problem with index u bigger than x" << endl;
        throw 50;
    }
    return xSize * uIndex - uIndex * (uIndex+1) / 2 + xIndex;
}

double grid::get(int x, int u){

    return gridPoints[getIndex(x, u)].value;
}

gridPoint& grid::getPoint(int xIndex, int uIndex) {
    return gridPoints[getIndex(xIndex, uIndex)];
}

void grid::set(int x, int u, double value){
    gridPoints[getIndex(x, u)].value = value;
}

void grid::setTime(int x, int u, double time) {
    gridPoints[getIndex(x, u)].u = time;
}

void grid::setPosition(int x, int u, double position) {
    gridPoints[getIndex(x,u)].x = position;
}

double grid::diferentiatePhi(int x, int u) {

    //in center
    if(x == u+1){
        return 0;
        return (gridPoints[getIndex(x, u-1)].value / functions::xToR(gridPoints[getIndex(x, u-1)].x) -
               gridPoints[getIndex(x-1, u-1)].value / functions::xToR(gridPoints[getIndex(x-1, u-1)].x))
        / (gridPoints[getIndex(x, u-1)].x - gridPoints[getIndex(x-1, u-1)].x);
    }


    if(gridPoints[getIndex(x, u)].x - gridPoints[getIndex(x-1, u)].x == 0){
        return 0;
    }

    return (gridPoints[getIndex(x, u)].value / functions::xToR(gridPoints[getIndex(x, u)].x) -
            gridPoints[getIndex(x-1, u)].value / functions::xToR(gridPoints[getIndex(x-1, u)].x))
           / (gridPoints[getIndex(x, u)].x - gridPoints[getIndex(x-1, u)].x);

}

void grid::setBoundaryConditions(double amplitude) {

    articleWave(amplitude);
}

void grid::setBoundaryConditions(double amplitude, double sigma) {

    articleWave(amplitude);
}



void grid::articleWave(double amplitude){

    gridPoints[getIndex(0, 0)].value = functions::articleGauss(gridPoints[getIndex(0, 0)].x, amplitude);
    gridPoints[getIndex(0, 0)].beta = 0;
    gridPoints[getIndex(0, 0)].m = 0;
    gridPoints[getIndex(0, 0)].u = 0;

    for(int i = 1; i < xSize; i++){

        double x0 = gridPoints[getIndex(i-1, 0)].x;
        double x1 = gridPoints[getIndex(i, 0)].x;

        gridPoints[getIndex(i, 0)].value = functions::articleGauss(gridPoints[getIndex(i, 0)].x, amplitude);
        gridPoints[getIndex(i, 0)].u = 0;
        double dphi = diferentiatePhi(i, 0);
        gridPoints[getIndex(i, 0)].beta = oneStepSolver::solveForBeta(x0, x1, gridPoints[getIndex(i-1, 0)].beta, dphi);
                                                                      //functions::derivedArticleGauss((x0 + x1)/2, amplitude));

        gridPoints[getIndex(i, 0)].m = oneStepSolver::solveForMass(x0, x1, gridPoints[getIndex(i-1, 0)].m, dphi);
                                                                      //functions::derivedArticleGauss((x0 + x1)/2, amplitude));


    }
}

int grid::getUIndexForTime(double u){
    for(int uIndex = 0; uIndex < uSize; uIndex++){
        if(getPoint(xSize-1, uIndex).u >= u){
            cout << uIndex;
            return uIndex;
        }
    }
    cout << "Time not found for task" << endl;
    throw 20;
}

void grid::destroyGrid() {
    delete [] gridPoints;
}

