#ifndef VECTORMATH_H
#define VECTORMATH_H
#include <cmath>

struct vector{
	double x;
	double y;
	double z;
	
};

inline vector addVectors(vector a,vector b){
	vector c = {a.x+b.x,a.y+b.y,a.z+b.z};
 
	return c;
}
 
inline vector scaleVector(double b,vector a){
	vector c = {b*a.x,b*a.y,b*a.z};
 
	return c;
}
 
inline vector subtractVectors(vector a,vector b){
	vector c = {a.x-b.x,a.y-b.y,a.z-b.z};
 
	return c;
}
 
inline double mod(vector a){
	return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
#endif
