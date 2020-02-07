#include <iostream>
#include <iomanip>
#include "grid/grid.h"
#include "solver/solverDICE.h"
#include "iofiles/writers.h"
#include "convergence/halfIntervalTester.h"
#include "generators/mainPlotsGenerators.h"

using namespace std;

//Find the critical amplitude.
void halfInterval(){
    cout << "starting half interval calculations" << endl;

    grid cGrid = grid(10000,10000);

    double eps = 1E-10;
    double upperBound = 0.15;
    double lowBound = 0.14;
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
        //uncoment to write all the data. Writing every tenth point in any direction.
        //writers::writeData(cGrid, "datafor" + writers::to_string_with_precision((upperBound + lowBound)/2, 15));

    } while (upperBound - lowBound > eps);

    //Two solutions. We can output anything we want using writers.

    cGrid.createGrid();
    cout << "plotting for lowbound: " << setprecision(15) << lowBound << endl;
    cGrid.setBoundaryConditions(lowBound);

    solverDICE::solve(cGrid);



    //writers::writeForContour(cGrid, "subcriticalPlot");
    //writers::writeGeodetics(cGrid, "subcriticalGeodetics");
    //writers::writeOutData(cGrid, "subcriticalOutput");


    cGrid.createGrid();
    cout << "plotting for uppbound: " << setprecision(15) << upperBound << endl;
    cGrid.setBoundaryConditions(upperBound);

    solverDICE::solve(cGrid);

    //writers::writeForContour(cGrid, "supercriticalPlot");
    //writers::writeGeodetics(cGrid, "supercriticalGeodetics");
    //writers::writeOutData(cGrid, "supercriticalOutput");


    cGrid.destroyGrid();

    cout << "Success! Amplitude average: " << setprecision(15) << (upperBound + lowBound) / 2 << endl;
}

//Call this method for one-time calculation. Set amplitude as you wish.
void singleInstance(){

    double amplitude = 0.144930566102266;

    cout << "starting" << endl;

    grid cGrid = grid(10000, 10000);

    cGrid.createGrid();


    cGrid.setBoundaryConditions(amplitude);

    solverDICE::solve(cGrid);

    writers::writeForContour(cGrid, "singleInstancePlot");
    //writers::writeMOverR(cGrid, "mOverRSingle");
    //writers::writeMPlot(cGrid, "supercriticalM");
    //writers::writeEUURPlot(cGrid, "singleInstanceEUUR");

    //writers::writeData(cGrid, "supercriticalPenrose");
    //writers::writemrContour(cGrid, "subcriticalmrContour");

    cGrid.destroyGrid();

    cout << "Success! " << endl;
}

void compareEUUR(){

    cout << "starting" << endl;
    int resolution = 5000;

    grid cGrid = grid(resolution, resolution);

    cGrid.createGrid();


    cGrid.setBoundaryConditions(0.1);//functions::AMPLITUDE);

    solverDICE::solve(cGrid);

    //writers::writeForContour(cGrid);
    //writers::writeEUURSlice(cGrid, cGrid.getUIndexForTime(2), "5000", 1);
    //cGrid.writeNonOrthogonal();
    //cGrid.writeOutData();
    //cGrid.writeGeodetics();

    grid doubleGrid = grid(resolution*2, resolution*2);

    doubleGrid.createGrid();


    doubleGrid.setBoundaryConditions(0.1);//functions::AMPLITUDE);

    solverDICE::solve(doubleGrid);

    //writers::writeForContour(cGrid);
    //writers::writeEUURSlice(doubleGrid, doubleGrid.getUIndexForTime(2), "10000", 1);
    //writers::writeEUURSlice(doubleGrid, doubleGrid.getUIndexForTime(2), "4x10000", 4);
    writers::writePsiDifPlot(cGrid, doubleGrid, "logRozdielu");
    //cGrid.writeNonOrthogonal();
    //cGrid.writeOutData();
    //cGrid.writeGeodetics();

    cGrid.destroyGrid();
    doubleGrid.destroyGrid();


    cout << "Success! " << endl;
}

void convergenceTest(){

    cout << "starting" << endl;

    int resolution = 1000;

    halfIntervalTester::testFullResolution(resolution);
    halfIntervalTester::testFullResolution(resolution*2);
    halfIntervalTester::testFullResolution(resolution*4);
    halfIntervalTester::testFullResolution(resolution*8);

    cout << "done" << endl;

}

void compareTwoTests(){

    cout << "starting" << endl;

    halfIntervalTester::compareTwoResolutions(8000);

    cout << "done" << endl;

}

void phaseDiagram(){

    grid cGrid = grid();

    double critical = 0.144930593706667;
    double eps = 0.000001;
    double criticalSigma = 0.3;
    double epsSigma = 0.001;


    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            cGrid.createGrid();
            cGrid.setBoundaryConditions(critical + (i-1) * eps, criticalSigma + (j-1) * epsSigma);

            solverDICE::solve(cGrid);

            writers::writeMOverR3D(cGrid, to_string(i+3*j));

        }
    }

}

//Main method. Call any calculation you wany from here. Uncommeny any line, uncomment any writers you wish to use in the method.
//Currently subcritical test is turned on with writing data for countour plot. Resolution is set in the method when constructing grid.
//TODO DONT FORGET TO SET OUTPUT PATH IN writers.cpp
int main() {

    singleInstance();

    //convergenceTest();
    //halfInterval();
    //compareTwoTests();
    //compareEUUR();
    //phaseDiagram();
    //mainPlotsGenerators::generateWeakData();
    //mainPlotsGenerators::generateStrongData();
    //mainPlotsGenerators::phaseGenerator();
    //mainPlotsGenerators::mOverRGenerator();

    return 0;

}