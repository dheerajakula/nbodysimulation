#include <iostream>
#include <fstream>
#include "nbody.h"
#include "VectorMath.h"


void initiateSystem(){
	
 	std::ifstream myReadFile;
 	myReadFile.open("init.txt");
 	if (myReadFile.is_open()) {
 		
		myReadFile >> GravConstant;
		myReadFile >> bodies;
		myReadFile >> timeStep;
		myReadFile >> totalTime;
		masses = new double[bodies];
		positions = new vector[bodies];
		velocities = new vector[bodies];
		accelerations = new vector[bodies];
		for(int i=0;i<bodies;i++){
			myReadFile >> masses[i];
			myReadFile >> positions[i].x >> positions[i].y >> positions[i].z;
			myReadFile >> velocities[i].x >> velocities[i].y >> velocities[i].z;
		}
	}
	
	myReadFile.close();
}

void removeEnergy(){
	int i,j;
 
	for(i=0;i<bodies;i++){
		for(j=0;j<bodies;j++){
			if(i!=j){
				if((abs(positions[i].x - positions[j].x) <= timeStep) && (abs(positions[i].y - positions[j].y) <= timeStep) && (abs(positions[i].z - positions[j].z) <= timeStep)){
	
					velocities[i] = scaleVector(1-timeStep*timeStep,velocities[i]);
					//accelerations[i] = scaleVector(1-timeStep,accelerations[i]);
				}
			}
			
		}
	}
}

void computeAccelerations(){
	int i,j;
 
	for(i=0;i<bodies;i++){
		accelerations[i].x = 0;
		accelerations[i].y = 0;
		accelerations[i].z = 0;
		for(j=0;j<bodies;j++){
			if(i!=j){
				double den = pow(mod(subtractVectors(positions[i],positions[j])),3);
				den = den + timeStep;
				accelerations[i] = addVectors(accelerations[i],scaleVector(GravConstant*masses[j]/den,subtractVectors(positions[j],positions[i])));
			}
		}
	}
}

void computeVelocities(){
	int i;
 
	for(i=0;i<bodies;i++)
		velocities[i] = addVectors(velocities[i],scaleVector(timeStep,accelerations[i]));
}
 
void computePositions(){
	int i;
 
	for(i=0;i<bodies;i++)
		positions[i] = addVectors(positions[i],scaleVector(timeStep,velocities[i]));
}

void simulate(){
	computeAccelerations();
	
	computeVelocities();
	removeEnergy();
	computePositions();
	timeElapsed = timeElapsed +timeStep;
}

void deletePointers(){
	delete[] masses;
	delete[] positions;
	delete[] velocities;
	delete[] accelerations;

}

void writeFile(){
	std::ofstream outfile;
   	outfile.open("data.dat");
	outfile << std::fixed;
	outfile.precision(4);
	for(int i=0;i<noOfSteps;i++){
		simulate();
		if(timeElapsed >= 0.05){
			for(int j=0;j<bodies;j++){
				//std::cout << positions[j].x;
				outfile<<positions[j].x<<' '<<positions[j].y<<' '<<positions[j].z<<' '<<std::endl;
			}
			timeElapsed = 0;
		}
			
	}
	outfile.close();
}
void writeFinal(){
	std::ofstream outfile;
   	outfile.open("final.txt");
	outfile << GravConstant << " " << bodies << " " <<timeStep << " "<<totalTime << std::endl;
	outfile << std::fixed;
	outfile.precision(4);
	for(int i=0;i<bodies;i++){
		outfile<<masses[i]<<std::endl;
		outfile<<positions[i].x<<' '<<positions[i].y<<' '<<positions[i].z<<' '<<std::endl;
		outfile<<velocities[i].x<<' '<<velocities[i].y<<' '<<velocities[i].z<<' '<<std::endl;
	}
		
	outfile.close();
}
int main(int argC,char* argV[])
{
	
	timeElapsed = 0;
	initiateSystem();
	noOfSteps = totalTime/timeStep;

	writeFile();
	writeFinal();
	deletePointers();
	return 0;
}