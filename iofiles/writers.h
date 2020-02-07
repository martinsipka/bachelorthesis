//
// Created by martin on 21.4.17.
//

#ifndef GRAVITYCOLLAPSE_WRITERS_H
#define GRAVITYCOLLAPSE_WRITERS_H

#include <iostream>
#include "../grid/grid.h"

//class for writing any output files.

class writers {

public:

    // TODO DONT FORGET TO CHANGE THE PATH TO YOUR DESIRED OUTPUT LOCATION.

    static const string PATH;
    static const string INITIAL_DATA_PATH;
    static const string CONVERGENCE_TEST_PATH;
    static const string PHASE_DIAGRAM;
    static const string BASE_OUTPUT_PATH;

    static void writeForContour(grid&, string name);

    static void writeOutData(grid&, string name);

    static void writeNonOrthogonal(grid&);

    static void writeGeodetics(grid &cGrid, string name);

    static void writeInitialData(grid &cGrid);

    static void writeMOverR(grid &cGrid, string name);

    static void writeMOverR(grid &cGrid, ofstream &myfile);

    static void writeBetas(grid &cGrid);

    static void writeMOverR3D(grid &cGrid, string name);


    static void writeEUURSlice(grid &cGrid, int poradie, string name, int multiply);

    static void writeData(grid &cGrid, string name);

    static string to_string_with_precision(double a_value, int n);

    static void printLocalMaxima(grid &cGrid);

    static void writeMPlot(grid &cGrid, string name);

    static void writeEUURPlot(grid &cGrid, string name);

    static void writePsiDifPlot(grid &cGrid, grid &doubleGrid, string name);

    static void writemrContour(grid &cGrid, string name);

    static void writeScriBeta(grid &cGrid, ofstream &name);

};


#endif //GRAVITYCOLLAPSE_WRITERS_H
