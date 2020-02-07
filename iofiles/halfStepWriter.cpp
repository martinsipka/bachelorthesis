//
// Created by martin on 9.4.17.
//

#include <fstream>
#include "halfStepWriter.h"
#include "writers.h"

void halfStepWriter::writeHalfStep(grid &fullGrid, grid &halfGrid) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "halfStepDif");

    int step = 1;
    for(int uIndex = 0; uIndex < halfGrid.uSize; uIndex += step) {


        myfile << fullGrid.getPoint(fullGrid.xSize-1, uIndex * 2).u << '\t'
                   << fullGrid.get(fullGrid.xSize-1, uIndex * 2) - halfGrid.get(halfGrid.xSize-1, uIndex) << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFraction(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fraction");

    int step = 1;
    for(int uIndex = 1; uIndex < xIndex; uIndex += step) {

        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).u << '\t'
               << log2((fullGridLow.get(xIndex * 2, uIndex * 2) - halfGridLow.get(xIndex, uIndex)) /
               (fullGrid.get(xIndex * 4, uIndex * 4) - halfGrid.get(xIndex * 2, uIndex * 2))) << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFractionBeta(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fractionBeta");

    int step = 1;
    for(int uIndex = 0; uIndex < xIndex; uIndex += step) {


        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).u << '\t'
               << log2((fullGridLow.getPoint(xIndex * 2, uIndex * 2).beta - halfGridLow.getPoint(xIndex, uIndex).beta) /
                  (fullGrid.getPoint(xIndex * 4, uIndex * 4).beta - halfGrid.getPoint(xIndex * 2, uIndex * 2).beta))

               << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFractionM(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int xIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fractionM");

    int step = 1;
    for(int uIndex = 0; uIndex < xIndex; uIndex += step) {


        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).u << '\t'
               << log2((fullGridLow.getPoint(xIndex * 2, uIndex * 2).m - halfGridLow.getPoint(xIndex, uIndex).m) /
                  (fullGrid.getPoint(xIndex * 4, uIndex * 4).m - halfGrid.getPoint(xIndex * 2, uIndex * 2).m))

               << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFractionHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fractionHorizontal");

    int step = 1;
    for(int xIndex = uIndex; xIndex < halfGridLow.xSize; xIndex += step) {


        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).x << '\t'
               << log2((fullGridLow.get(xIndex * 2, uIndex * 2) - halfGridLow.get(xIndex, uIndex)) /
                  (fullGrid.get(xIndex * 4, uIndex * 4) - halfGrid.get(xIndex * 2, uIndex * 2)))

               << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFractionBetaHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fractionBetaHorizontal");

    int step = 1;
    for(int xIndex = uIndex; xIndex < halfGridLow.uSize; xIndex += step) {


        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).x << '\t'
               << log2((fullGridLow.getPoint(xIndex * 2, uIndex * 2).beta - halfGridLow.getPoint(xIndex, uIndex).beta) /
                  (fullGrid.getPoint(xIndex * 4, uIndex * 4).beta - halfGrid.getPoint(xIndex * 2, uIndex * 2).beta))

               << endl;
    }

    myfile.close();

}

void halfStepWriter::writeFractionMHorizontal(grid &fullGrid, grid &halfGrid, grid &fullGridLow, grid &halfGridLow, int uIndex) {

    cout << "writing output for: " << fullGrid.xSize << endl;
    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + "fractionMHorizontal");

    int step = 1;
    for(int xIndex = uIndex; xIndex < halfGridLow.uSize; xIndex += step) {


        myfile << fullGrid.getPoint(xIndex * 4, uIndex * 4).x << '\t'
               << log2((fullGridLow.getPoint(xIndex * 2, uIndex * 2).m - halfGridLow.getPoint(xIndex, uIndex).m) /
                  (fullGrid.getPoint(xIndex * 4, uIndex * 4).m - halfGrid.getPoint(xIndex * 2, uIndex * 2).m))

               << endl;
    }

    myfile.close();

}