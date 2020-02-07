# Bachelor thesis
## Gravitational Collapse of a scalar field

Simulation of a gravitational collapse in spherical symmetry. System of [PDR](https://en.wikipedia.org/wiki/Einstein_field_equations) is simplified to a system of ordinary differential equations.

BEFORE COMPILATION: Open file source/iofiles.cpp and specify the variable PATH, where you want to output the data.

Run "cmake ." command in the directory "source". After cmake generates a makefile run "make". This will build the executable gravitatitonalCollapse. When run, the executable will be calculating contour plot data fot slightly subcritical data with resolution 10 000 x 10 000 gridpoints. 

