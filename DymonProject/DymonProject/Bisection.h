//created by Wang Jianwei on 1 Dec 2012
#ifndef BISECTION_H
#define BISECTION_H
#include "AbstractNumerical.h"
#include <cmath>

namespace utilities{
	template <class T> class Bisection: public AbstractNumerical<T>{

	public:

		Bisection(T* callerObj, double (T::*func) (double d)):AbstractNumerical(callerObj){_func = func;};

		double findRoot(double startVal, double endVal, double tolerance, int iterateCount);

	private:

		double (T::*_func) (double d);

	};

	template <class T> 
	double Bisection<T>::findRoot(double startVal, double endVal, double tolerance, int iterateCount){

		double startY = (*_callerObj.*_func)(startVal);
		double endY = (*_callerObj.*_func)(endVal);

		if (startY*endY>0)
			throw "Invalid startVal or endVal!";
		if (startY==0)
			return startVal;
		if (endY==0)
			return endVal;

		double midVal;
		double y;
		for (int i = 0; i < iterateCount; i++) {        
			midVal = (startVal + endVal) / 2; 
			y = (*_callerObj.*_func)(midVal);
			if (y==0 || abs((endVal-startVal)/2)<tolerance){
				return midVal;
			}else if (y*(*_callerObj.*_func)(startVal) < 0) {
				endVal = midVal;
			} else  {
				startVal = midVal;
			} 
		}
		throw "Root Not Found after all iterations!";
	}
}
#endif