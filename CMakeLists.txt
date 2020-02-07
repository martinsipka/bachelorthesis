cmake_minimum_required(VERSION 3.5)
project(gravitycollapse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp grid/grid.cpp grid/grid.h solver/solverDICE.cpp solver/solverDICE.h grid/gridPoint.cpp grid/gridPoint.h ODESolvers/geodeticsSolver.cpp ODESolvers/geodeticsSolver.h ODESolvers/functions.cpp ODESolvers/functions.h grid/interpolator.cpp grid/interpolator.h ODESolvers/oneStepSolver.cpp ODESolvers/oneStepSolver.h iofiles/halfStepWriter.cpp iofiles/halfStepWriter.h iofiles/writers.cpp iofiles/writers.h convergence/halfIntervalTester.cpp convergence/halfIntervalTester.h generators/mainPlotsGenerators.cpp generators/mainPlotsGenerators.h)
add_executable(graviationalCollapse ${SOURCE_FILES})
