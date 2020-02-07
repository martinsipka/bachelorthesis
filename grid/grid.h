//
// Created by martin on 5.3.17.
//

#ifndef GRAVITYCOLLAPSE_GRID_H
#define GRAVITYCOLLAPSE_GRID_H

#include <iostream>
#include <cmath>
#include "gridPoint.h"

using namespace std;

//Class for operations with grid.

class grid {

public:

    static constexpr double xStep = 0.0001;
    static constexpr double uStep = 0.0001;

    static constexpr int DEFAULT_X_SIZE = 1000;
    static constexpr int DEFAULT_U_SIZE = 1000;

    int xSize;
    int uSize;

    gridPoint *gridPoints;

    int getIndex(int xIndex, int uIndex);

    grid();

    grid(int xS, int uS);

    void createGrid();

    void setBoundaryConditions(double amplitude);

    void setBoundaryConditions(double amplitude, double sigma);

    double get(int x, int u);

    void set(int x, int u, double value);

    gridPoint& getPoint(int xIndex, int uIndex);

    void setTime(int x, int u, double time);

    void setPosition(int x, int u, double position);

    void articleWave(double amplitude);

    double diferentiatePhi(int x, int u);

    int getUIndexForTime(double time);

    void destroyGrid();



};

//defining on heap

#endif //GRAVITYCOLLAPSE_GRID_H
