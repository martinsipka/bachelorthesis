//
// Created by martin on 21.4.17.
//

#include "halfIntervalTester.h"
#include "../grid/grid.h"
#include "../solver/solverDICE.h"
#include "../iofiles/halfStepWriter.h"
#include "../iofiles/writers.h"

void halfIntervalTester::testFullResolution(int fullResolution){

    grid cGrid = grid(fullResolution, fullResolution);

    cGrid.createGrid();

    cGrid.setBoundaryConditions(0.01);//functions::AMPLITUDE); weak data

    solverDICE::solve(cGrid);

    cout << "counted full" << endl;

    grid halfStep = grid(fullResolution / 2 - 1, fullResolution / 2 - 1);

    halfStep.createGrid();

    halfStep.setBoundaryConditions(0.01);//functions::AMPLITUDE); weak data

    solverDICE::solve(halfStep);

    halfStepWriter::writeHalfStep(cGrid, halfStep);

    halfStep.destroyGrid();
    cGrid.destroyGrid();

    cout << "Success! " << endl;

}

void halfIntervalTester::compareTwoResolutions(int maxFull) {

    grid cGrid = grid(maxFull, maxFull);

    cGrid.createGrid();

    cGrid.setBoundaryConditions(0.01);//functions::AMPLITUDE); weak data

    solverDICE::solve(cGrid);

    cout << "counted full" << endl;

    grid halfStep = grid(maxFull / 2 , maxFull / 2 );

    halfStep.createGrid();

    halfStep.setBoundaryConditions(0.01);//functions::AMPLITUDE); weak data

    solverDICE::solve(halfStep);

    grid halfStepLow = grid(maxFull / 4 , maxFull / 4);

    halfStepLow.createGrid();

    halfStepLow.setBoundaryConditions(0.01);//functions::AMPLITUDE); weak data

    solverDICE::solve(halfStepLow);

    halfStepWriter::writeFraction(cGrid, halfStep, halfStep, halfStepLow, 1500);
    halfStepWriter::writeFractionBeta(cGrid, halfStep, halfStep, halfStepLow, 1500);
    halfStepWriter::writeFractionM(cGrid, halfStep, halfStep, halfStepLow, 1500);

    halfStepWriter::writeFractionHorizontal(cGrid, halfStep, halfStep, halfStepLow, 40);
    halfStepWriter::writeFractionBetaHorizontal(cGrid, halfStep, halfStep, halfStepLow, 40);
    halfStepWriter::writeFractionMHorizontal(cGrid, halfStep, halfStep, halfStepLow, 40);

    writers::writeOutData(cGrid, "output");




    halfStep.destroyGrid();
    cGrid.destroyGrid();

    cout << "Success! " << endl;

}