#ifndef NBODY_H
#define NBODY_H
#include "VectorMath.h"
int bodies;
int noOfSteps;
double timeStep;
double totalTime;
double timeElapsed;
double *masses,GravConstant;
vector *positions,*velocities,*accelerations;
void initiateSystem();
void computeAccelerations();
void computeVelocities();
void computePositions();
void simulate();
#endif
