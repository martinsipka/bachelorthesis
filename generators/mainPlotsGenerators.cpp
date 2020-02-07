//
// Created by martin on 1.5.17.
//

#include <fstream>
#include "mainPlotsGenerators.h"
#include "../grid/grid.h"
#include "../solver/solverDICE.h"
#include "../iofiles/writers.h"
#include "../ODESolvers/functions.h"

void mainPlotsGenerators::generateWeakData(){

    cout << "starting" << endl;

    grid cGrid = grid(10000, 10000);

    cGrid.createGrid();


    cGrid.setBoundaryConditions(0.001);//0.144930592706667);

    solverDICE::solve(cGrid);

    /*writers::writeForContour(cGrid, "weakPlot");


    writers::writeEUURSlice(cGrid, cGrid.getUIndexForTime(2.0), "weakEUUR", 1);

    writers::writeGeodetics(cGrid, "weakGeodetics");
    writers::writeOutData(cGrid, "weakOutput");*/
    //writers::writeMPlot(cGrid, "weakMPlot");

    writers::writeData(cGrid, "weakDataMath.txt");

    //writers::writeInitialData(cGrid);

    cGrid.destroyGrid();


    cout << "Success! " << endl;
}

void mainPlotsGenerators::generateStrongData(){

    cout << "starting" << endl;

    grid cGrid = grid(10000, 10000);

    cGrid.createGrid();


    cGrid.setBoundaryConditions(0.2);//0.144930592706667);

    solverDICE::solve(cGrid);

    /*writers::writeForContour(cGrid, "strongPlot");


    writers::writeEUURSlice(cGrid, cGrid.getUIndexForTime(1.0), "strongEUUR", 1);

    writers::writeGeodetics(cGrid, "strongGeodetics");
    writers::writeOutData(cGrid, "strongOutput");

    //writers::writeInitialData(cGrid);*/

    //writers::writeMPlot(cGrid, "strongMPlot");
    writers::writeData(cGrid, "stringDataMath.txt");

    cGrid.destroyGrid();


    cout << "Success! " << endl;
}

void mainPlotsGenerators::phaseGenerator(){

    cout << "starting" << endl;

    grid cGrid = grid(1000,1000);

    /*cGrid.createGrid();*/
    double eps = 1E-5;
    double upperBound = 0.15;
    double lowBound = 0.14;

    ofstream myfile;
    myfile.open(writers::PHASE_DIAGRAM + "phaseDiagram");

    do {

        cGrid.createGrid();
        cGrid.setBoundaryConditions((upperBound + lowBound) / 2);

        if (solverDICE::solve(cGrid)) {
            upperBound = (upperBound + lowBound) / 2;
            cout << "bf found for amplitude: " << (upperBound + lowBound) / 2 << endl;
        } else {
            cout << "bf not found for amplitude: " << (upperBound + lowBound) / 2 << endl;
            lowBound = (upperBound + lowBound) / 2;
        }


        for(int uIndex = 0; uIndex < cGrid.uSize; uIndex++){
            double maxUOverR = 0.0;
            double maxBetaDerivative = 0.0;
            for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex++) {
                double mass = 2 * cGrid.getPoint(xIndex, uIndex).m / functions::xToR(cGrid.getPoint(xIndex, uIndex).x);
                if (mass > maxUOverR) {
                    maxUOverR = mass;
                }
                if (xIndex > uIndex && uIndex < cGrid.uSize - 5) {
                    double dBeta = abs(functions::dPsidt(cGrid, xIndex, uIndex));
                    if (dBeta > maxBetaDerivative) {
                        maxBetaDerivative = dBeta;
                    }
                }

            }
            if(maxUOverR > 0 && cGrid.getPoint(cGrid.xSize-1, uIndex).u > 0) {
                if(cGrid.getPoint(cGrid.xSize - 1, uIndex).beta > 1){
                    cGrid.getPoint(cGrid.xSize - 1, uIndex).beta = 1;
                }
                myfile <<  cGrid.getPoint(cGrid.xSize - 1, uIndex).u  << '\t'
                       << maxBetaDerivative
                       << '\t' << maxUOverR << endl;
            }
        }

        myfile << endl;
        myfile << endl;

    } while (upperBound - lowBound > eps);

    myfile.close();

    cout << "succes" << endl;
}

void mainPlotsGenerators::mOverRGenerator() {
    cout << "starting" << endl;

    grid cGrid = grid(1000,1000);

    /*cGrid.createGrid();*/
    double eps = 1E-10;
    double upperBound = 0.145;
    double lowBound = 0.1449;

    ofstream myfile;
    myfile.open(writers::BASE_OUTPUT_PATH + "mOverR");

    do {

        cGrid.createGrid();
        cGrid.setBoundaryConditions((upperBound + lowBound) / 2);

        if (solverDICE::solve(cGrid)) {
            upperBound = (upperBound + lowBound) / 2;
            cout << "bf found for amplitude: " << (upperBound + lowBound) / 2 << endl;
        } else {
            cout << "bf not found for amplitude: " << (upperBound + lowBound) / 2 << endl;
            lowBound = (upperBound + lowBound) / 2;
        }


        writers::writeMOverR(cGrid, myfile);

        myfile << endl;
        myfile << endl;

    } while (upperBound - lowBound > eps);

    myfile.close();

    cout << "succes" << endl;
}
