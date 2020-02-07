#include "solverDICE.h"
#include "../ODESolvers/geodeticsSolver.h"
#include "../grid/interpolator.h"
#include "../ODESolvers/oneStepSolver.h"
#include "../ODESolvers/functions.h"

//Basic solve method. Pass created grid reference with initial data as an argument.
bool solverDICE::solve(grid &cGrid){

    for(int uIndex = 1; uIndex < cGrid.uSize; uIndex++){

        gridPoint& pastPoint = cGrid.getPoint(uIndex, uIndex-1);


        double u = geodeticsSolver::solveTimestep(pastPoint.x, pastPoint.u);
        if(u < 0 ){
            return true;
        }

        if (u > 5) {
            //Stopping for time is up.
           break;
        }

        cGrid.setTime(uIndex, uIndex, u);
        cGrid.setPosition(uIndex, uIndex, 0.0);

        for(int xIndex = uIndex + 1; xIndex < cGrid.xSize; xIndex++){

            double x;
            if(xIndex == cGrid.xSize-1){
                x = 1.0;

            } else {

                gridPoint &past = cGrid.getPoint(xIndex, uIndex - 1);

                x = geodeticsSolver::solvePositionOneStep(past.x, past.u, u, past.beta, past.m, xIndex, uIndex, cGrid);


            }

            cGrid.setPosition(xIndex, uIndex, x);
            cGrid.setTime(xIndex, uIndex, u);

            double newValue = cGrid.get(xIndex-1, uIndex) + cGrid.get(xIndex, uIndex-1)
                                        - cGrid.get(xIndex-1, uIndex-1) - integrateStep(cGrid, xIndex, uIndex);
            cGrid.set(xIndex, uIndex, newValue);

            double dphi = cGrid.diferentiatePhi(xIndex, uIndex);

            cGrid.getPoint(xIndex, uIndex).beta = oneStepSolver::solveForBeta(cGrid.getPoint(xIndex-1, uIndex).x,
                                                                            cGrid.getPoint(xIndex, uIndex).x, cGrid.getPoint(xIndex-1, uIndex).beta, dphi);

            cGrid.getPoint(xIndex, uIndex).m = oneStepSolver::solveForMass(cGrid.getPoint(xIndex-1, uIndex).x,
                                                                         cGrid.getPoint(xIndex, uIndex).x, cGrid.getPoint(xIndex-1, uIndex).m, dphi);

            if(geodeticsSolver::checkDerivative(cGrid.getPoint(xIndex, uIndex).x, cGrid.getPoint(xIndex, uIndex).m)){
                //Black hole was found
                return true;
            }

        }

    }

    solverDICE::checkEUUR(cGrid);

    return false;

}

//Count and write EUUR.
void solverDICE::checkEUUR(grid &cGrid){
    for(int uIndex = 1; uIndex < cGrid.uSize; uIndex++) {

        for (int xIndex = uIndex + 1; xIndex < cGrid.xSize; xIndex++) {
            cGrid.getPoint(xIndex, uIndex).euur = functions::EUUR(cGrid, xIndex, uIndex);

        }
    }
}

//Count the integral.
double solverDICE::integrateStep(grid &cGrid, int xIndex, int uIndex){


    return interpolator::getIntegratedArea(cGrid, xIndex, uIndex) * exp(2*interpolator::getMiddleBeta(cGrid, xIndex, uIndex)) *
           interpolator::getMiddleM(cGrid, xIndex, uIndex) * interpolator::getMiddlePhi(cGrid, xIndex, uIndex);

}

//Simple but fast power function for integer e.
double solverDICE::power(double x, int e) {
    double p = x;
    for (int i = 0; i < e - 1; i++) {
        p *= x;
    }
    return p;
}
