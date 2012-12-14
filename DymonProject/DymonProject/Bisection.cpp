//created by Wang Jianwei on 1 Dec 2012

#include "Bisection.h"

using namespace utilities;

double Bisection::findRoot(double startVal, double endVal, double tolerance, int iterateCount){
	
	if (_func(startVal)*_func(endVal)>0)
		throw "Invalid startVal or endVal!";
	if (_func(startVal)==0)
		return startVal;
	if (_func(endVal)==0)
		return endVal;

	double midVal;
	double y;
	for (int i = 0; i < iterateCount; i++) {        
		midVal = (startVal + endVal) / 2; 
		y = _func(midVal);
		if (y=0 || (endVal-startVal)/2<tolerance){
			return midVal;
		}else if (y*_func(startVal) < 0) {
			endVal = midVal;
		} else  {
			startVal = midVal;
		} 
	}
	throw "Root Not Found after all iterations!";
}