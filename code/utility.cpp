#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "VectorMath.h"
int bodies;
double timeStep;
double totalTime;
double *masses,GravConstant;
vector *positions,*velocities;

bool is_perfect_cube(int n) {
    int root(round(cbrt(n)));
    return n == root * root * root;
}

void generateInit(){
	
    std::ofstream outfile;
	
    outfile.open("init.txt");
	outfile << GravConstant << " " << bodies << " " <<timeStep << " "<<totalTime << std::endl;
	if (is_perfect_cube(bodies)){
		int num = round(cbrt(bodies));
		for(int z = 0;z < num;z++){
			for(int y = 0;y < num ;y++){
				for(int x = 0;x < num;x ++){
					outfile << rand()%9+1 << std::endl;
					outfile << x*10 << " "<< y*10 <<" " << z*10 << std::endl;
					outfile << 0 <<" "<< 0<<" "<< 0 << std::endl;
				}
			}
		}
	}
	else{
		for(int i=0;i<bodies;i++){
			outfile << rand()%9+1 << std::endl;
            outfile << rand()%10 << " "<<rand()%10<<" " << rand()%10 << std::endl;
            outfile << 0 <<" "<< 0<<" "<< 0 << std::endl;
		}

	}
	
    outfile.close();
}
void calculateEnergy(std::string filename){
	double KE = 0;
	double PE = 0;
	double TE = 0;
	double distance = 0;
	std::ifstream myReadFile;
 	myReadFile.open(filename);
 	if (myReadFile.is_open()) {
 		
		myReadFile >> GravConstant;
		myReadFile >> bodies;
		myReadFile >> timeStep;
		myReadFile >> totalTime;
		masses = new double[bodies];
		positions = new vector[bodies];
		velocities = new vector[bodies];
		for(int i=0;i<bodies;i++){
			myReadFile >> masses[i];
			myReadFile >> positions[i].x >> positions[i].y >> positions[i].z;
			myReadFile >> velocities[i].x >> velocities[i].y >> velocities[i].z;
		}
	}
	for(int i=0;i<bodies;i++){
		KE = KE + 0.5*masses[i]*pow(mod(velocities[i]),2);		
	}
	for(int i=0;i<bodies;i++){
		for(int j=0;j<bodies;j++){
			if(i!=j){
				distance = mod(subtractVectors(positions[i],positions[j]));
				PE = PE + GravConstant*masses[i]*masses[j]/distance;
			}
		}
	}
	PE = PE/2;
	TE = KE - PE;
	std::cout << "KE: "<< KE << std::endl;
	std::cout << "PE: " << PE << std::endl;
	std::cout << "TE: " << TE << std::endl;
}
int main(int argc,char *argv[])
{
	std::ifstream myReadFile;
	myReadFile.open("meta.txt");
    if (myReadFile.is_open()) {
 		
		myReadFile >> GravConstant;
		myReadFile >> bodies;
		myReadFile >> timeStep;
		myReadFile >> totalTime;
	}
    myReadFile.close();
	std::string arg1="";
	std::string arg2="";
	if(argv[1])	arg1 = argv[1];
	if(argv[2]) arg2 = argv[2];
    if(arg1 == "i"){
		std::cout << "into init" << std::endl;
		generateInit();
	}
	if(arg1 == "e"){
		std::cout << "into calculate energy" << std::endl;
		std::cout << arg2 << std::endl;
		calculateEnergy(arg2);
	}
	return 0;
}