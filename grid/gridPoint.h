//
// Created by martin on 29.3.17.
//

#ifndef GRAVITYCOLLAPSE_GRIDPOINT_H
#define GRAVITYCOLLAPSE_GRIDPOINT_H

//Gridpoint container class.

class gridPoint {

public:

    int xIndex = 0;
    int uIndex = 0;

    double value = 0;

    //distance from center
    double x = 0;

    //possition on graph
    double u = -1;

    double m = 0;
    double beta = 0;

    double euur = 0;

    //Default constructor
    gridPoint();

    //public methods

};


#endif //GRAVITYCOLLAPSE_GRIDPOINT_H
