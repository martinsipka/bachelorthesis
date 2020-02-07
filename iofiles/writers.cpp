//
// Created by martin on 21.4.17.
//

#include <fstream>
#include <sstream>
#include <iomanip>
#include "writers.h"
#include "../ODESolvers/functions.h"

using namespace std;

//TODO change the output path.
const string writers::PATH = "CHANGE ME!!";
const string writers::INITIAL_DATA_PATH = PATH + "initialData/";
const string writers::CONVERGENCE_TEST_PATH = PATH + "convergenceTest/";
const string writers::PHASE_DIAGRAM = PATH + "phaseDiagram/";
const string writers::BASE_OUTPUT_PATH = PATH + "mainPlots/";

void writers::writeForContour(grid &cGrid, string name) {
    cout << "writing contourPlot" << endl;
    ofstream myfile;
    myfile.open (BASE_OUTPUT_PATH + name);

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){

            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                       << cGrid.get(xIndex, uIndex) << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();

}

void writers::writeOutData(grid &cGrid, string name) {

    cout << "writing output" << endl;
    ofstream myfile;
    myfile.open (BASE_OUTPUT_PATH + name);

    int pointsOnGraph = cGrid.xSize;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {

        if (cGrid.getPoint(cGrid.xSize-1, uIndex).u >= 0) {
            myfile << cGrid.getPoint(cGrid.xSize-1, uIndex).u << '\t'
                   << cGrid.get(cGrid.xSize-1, uIndex) << endl;
        } else {
            //cout << "not a point" << endl;
        }
    }

    myfile.close();

}

void writers::writeNonOrthogonal(grid &cGrid) {
    cout << "writing" << endl;
    ofstream myfile;
    myfile.open (BASE_OUTPUT_PATH + "plot");

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){

            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x + cGrid.getPoint(uIndex, uIndex).u << '\t'
                       << cGrid.getPoint(xIndex, uIndex).u << '\t' << cGrid.get(xIndex, uIndex) << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();
}

void writers::writeGeodetics(grid &cGrid, string name) {
    cout << "writing geodetics" << endl;
    ofstream myfile;
    myfile.open (BASE_OUTPUT_PATH + name);

    int step = 200;

    cout << "plotting geodetics with step: " << step << endl;

    for(int xIndex = 0; xIndex < cGrid.xSize; xIndex += step){
        for(int uIndex = 0; uIndex < xIndex + 1; uIndex += 1) {


            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x << '\t'
                       << cGrid.getPoint(xIndex, uIndex).u << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();
}

void writers::writeInitialData(grid &cGrid){
    {
        cout << "writing initialWave" << endl;
        ofstream myfile;
        myfile.open(INITIAL_DATA_PATH + "InitialWave");

        for (int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

            myfile << cGrid.getPoint(xIndex, 0).x << '\t' << cGrid.get(xIndex, 0) << endl;

        }

        myfile.close();

        cout << "writing initial beta" << endl;
        ofstream myfile2;
        myfile2.open(INITIAL_DATA_PATH + "InitialBeta");

        for (int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

            myfile2 << cGrid.getPoint(xIndex, 0).x << '\t' << cGrid.getPoint(xIndex, 0).beta << endl;

        }

        myfile2.close();

        cout << "writing initial m" << endl;
        ofstream myfile3;
        myfile3.open(INITIAL_DATA_PATH + "InitialM");

        for (int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

            myfile3 << cGrid.getPoint(xIndex, 0).x << '\t' << cGrid.getPoint(xIndex, 0).m << endl;

        }

        myfile3.close();
    }

    cout << "writing initialWave in r" << endl;
    ofstream myfile;
    myfile.open (INITIAL_DATA_PATH + "InitialWaveInR");

    for(int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

        myfile << functions::xToR(cGrid.getPoint(xIndex, 0).x) << '\t' << cGrid.get(xIndex, 0) << endl;

    }

    myfile.close();

    cout << "writing initial beta in r" << endl;
    ofstream myfile2;
    myfile2.open (INITIAL_DATA_PATH + "InitialBetaInR");

    for(int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

        myfile2 << functions::xToR(cGrid.getPoint(xIndex, 0).x) << '\t' << cGrid.getPoint(xIndex, 0).beta << endl;

    }

    myfile2.close();

    cout << "writing initial m in r" << endl;
    ofstream myfile3;
    myfile3.open (INITIAL_DATA_PATH + "InitialMInR");

    for(int xIndex = 0; xIndex < cGrid.xSize; xIndex++) {

        myfile3 << functions::xToR(cGrid.getPoint(xIndex, 0).x) << '\t' << cGrid.getPoint(xIndex, 0).m << endl;

    }

    myfile3.close();
}

void writers::writeMOverR(grid &cGrid, string name) {
    ofstream myfile;
    myfile.open(writers::BASE_OUTPUT_PATH + name);
    writeMOverR(cGrid, myfile);
    myfile.close();
}

void writers::writeMOverR(grid &cGrid, ofstream &myfile) {

    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex++){
        double maxUOverR = 0.0;
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex++){
            double mass = 2 * cGrid.getPoint(xIndex, uIndex).m / functions::xToR(cGrid.getPoint(xIndex, uIndex).x);
            if(mass > maxUOverR){
                maxUOverR = mass;
            }
        }
        if(maxUOverR > 0)
            if(cGrid.getPoint(cGrid.xSize-1, uIndex).u > 0) {
                myfile << cGrid.getPoint(cGrid.xSize-1, uIndex).u << '\t' << maxUOverR << endl;
            }
    }
}

void writers::writeBetas(grid &cGrid) {
    ofstream myfile;
    myfile.open (PHASE_DIAGRAM + "beta");

    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex++){
            myfile << cGrid.getPoint(cGrid.xSize-1, uIndex).u << '\t' << cGrid.getPoint(cGrid.xSize-1, uIndex).beta << endl;
    }
    myfile.close();
}

void writers::writeMOverR3D(grid &cGrid, string name) {
    ofstream myfile;
    myfile.open (PHASE_DIAGRAM + "mass" + name);

    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex++){
        double maxUOverR = 0.0;
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex++){
            double mass = 2 * cGrid.getPoint(xIndex, uIndex).m / functions::xToR(cGrid.getPoint(xIndex, uIndex).x);
            if(mass > maxUOverR){
                maxUOverR = mass;
            }
        }
        if(maxUOverR > 0)
            myfile << cGrid.getPoint(cGrid.xSize-1, uIndex).u << '\t' <<  "s" << '\t' << maxUOverR << endl;
    }
    myfile.close();
}

void writers::writeEUURSlice(grid &cGrid, int poradie, string name, int multiply) {

    cout << "writing euur" << endl;
    ofstream myfile;
    myfile.open (CONVERGENCE_TEST_PATH + "euur" + name);

    int uIndex = poradie;
    int step = 1;
    cout << "plotting with step: " << step << endl;

    double maximum = functions::maximumEUURUSlice(cGrid, uIndex);

    for(int xIndex = uIndex; xIndex < cGrid.xSize-1; xIndex += (multiply-1)*50 +1){

        if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
            myfile << cGrid.getPoint(xIndex, uIndex).x << '\t'
                       << functions::normalizedEUUR(cGrid.getPoint(xIndex, uIndex).euur, maximum) * multiply << endl;
            } else {
                //cout << "not a point" << endl;
        }
    }

    myfile.close();

}

void writers::writeData(grid &cGrid, string name) {

    cout << "writing data" << endl;
    ofstream myfile;
    myfile.open (name);

    int step = 10;
    //myfile << "x" << '\t' << "u" << '\t'
    //          << "psi" << '\t' << "beta" << '\t' << "m" << '\t' << "euur" <<endl;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){
            gridPoint point = cGrid.getPoint(xIndex, uIndex);
            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << point.x << '\t' << point.u << '\t'
                       << cGrid.get(xIndex, uIndex) << '\t' << point.beta << '\t' << point.m << '\t' << point.euur <<endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
    }

    myfile.close();

}

std::string writers::to_string_with_precision(double a_value, int n){
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

void writers::printLocalMaxima(grid &cGrid){
    ofstream myfile;
    myfile.open (writers::BASE_OUTPUT_PATH + "MAXIMAS");

    double pastpastU = 0;
    double pastPast2m = 0;

    double pastU = 0;
    double past2m = 0;

    for(int uIndex = 5; uIndex < cGrid.uSize; uIndex++) {
        double maxUOverR = 0.0;
        for (int xIndex = uIndex; xIndex < cGrid.xSize; xIndex++) {
            double mass = 2 * cGrid.getPoint(xIndex, uIndex).m / functions::xToR(cGrid.getPoint(xIndex, uIndex).x);
            if (mass > maxUOverR) {
                maxUOverR = mass;
            }
        }
        if (maxUOverR > 0) {
            if(past2m > pastPast2m && past2m > maxUOverR) {
                if (cGrid.getPoint(cGrid.xSize - 1, uIndex).u > 0) {
                    myfile << pastU << '\t' << past2m << endl;
                }
            }
        }
        pastPast2m = past2m;
        pastpastU = pastU;
        past2m = maxUOverR;
        pastU = cGrid.getPoint(cGrid.xSize - 1, uIndex).u;
    }

    myfile.close();

}

void writers::writeMPlot(grid &cGrid, string name) {

    ofstream myfile;
    myfile.open (writers::BASE_OUTPUT_PATH + name);

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){

            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                       << cGrid.getPoint(xIndex, uIndex).m << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();

}

void writers::writeEUURPlot(grid &cGrid, string name) {

    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + name);

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){

            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                       << log10(abs(1/cGrid.getPoint(xIndex, uIndex).euur)) << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();

}

void writers::writePsiDifPlot(grid &cGrid, grid &doubleGrid, string name) {

    ofstream myfile;
    myfile.open (writers::CONVERGENCE_TEST_PATH + name);

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += step){



            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                if(cGrid.get(xIndex, uIndex) - doubleGrid.get(xIndex*2, uIndex*2) < 1E-16){
                    myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                           << 0 << endl;
                } else {
                    myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                           << log10(1 / (cGrid.get(xIndex, uIndex) - doubleGrid.get(xIndex * 2, uIndex * 2))) << endl;
                }
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();

}

void writers::writemrContour(grid &cGrid, string name) {

    cout << "writing contourPlot" << endl;
    ofstream myfile;
    myfile.open (BASE_OUTPUT_PATH + name);

    int pointsOnGraph = 1000;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += 10) {
        for(int xIndex = uIndex; xIndex < cGrid.xSize; xIndex += 2){

            if (cGrid.getPoint(xIndex, uIndex).u >= 0) {
                myfile << cGrid.getPoint(xIndex, uIndex).x << '\t' << cGrid.getPoint(xIndex, uIndex).u << '\t'
                       << 2*cGrid.getPoint(xIndex, uIndex).m / functions::xToR(cGrid.getPoint(xIndex, uIndex).x) << endl;
            } else {
                //cout << "not a point" << endl;
            }
        }
        myfile << endl;
    }

    myfile.close();

}

void writers::writeScriBeta(grid &cGrid, ofstream &myfile) {

    cout << "writing output" << endl;


    int pointsOnGraph = cGrid.xSize;
    int step = cGrid.xSize / pointsOnGraph;
    for(int uIndex = 0; uIndex < cGrid.uSize; uIndex += step) {

        if (cGrid.getPoint(cGrid.xSize-1, uIndex).u >= 0) {
            myfile << cGrid.getPoint(cGrid.xSize-1, uIndex).u << '\t'
                   << cGrid.getPoint(cGrid.xSize-1, uIndex).beta << endl;
        } else {
            //cout << "not a point" << endl;
        }
    }

    myfile << endl;
}