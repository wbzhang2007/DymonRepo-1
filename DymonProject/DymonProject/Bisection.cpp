//created by Wang Jianwei on 1 Dec 2012

#include "Bisection.h"
#include <iostream>

using namespace utilities;
using namespace std;

double Bisection::findRoot(targetFuncT func, double startVal, double endVal, double tolerance, int iterateCount){
	
	if (func(startVal)*func(endVal)>0)
		throw "Invalid startVal or endVal!";
	if (func(startVal)==0)
		return startVal;
	if (func(endVal)==0)
		return endVal;

	double midVal;
	double y;
	for (int i = 0; i < iterateCount; i++) {        
		midVal = (startVal + endVal) / 2; 
		y = func(midVal);
		if (y=0 || (endVal-startVal)/2<tolerance){
			return midVal;
		}else if (y*func(startVal) < 0) {
			endVal = midVal;
		} else  {
			startVal = midVal;
		} 
	}
	throw "Root Not Found after all iterations!";
}