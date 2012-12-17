//created by Wang Jianwei on 1 Dec 2012
#ifndef BISECTION_H
#define BISECTION_H
#include "AbstractNumerical.h"
#include <cmath>

namespace utilities{
	template <class T> class Bisection: public AbstractNumerical<T>{

	public:

		Bisection(T* callerObj, double (T::*func) (double d)):AbstractNumerical(callerObj){_func = func;};

		float findRoot(float startVal, float endVal, float tolerance, int iterateCount);

	private:

		double (T::*_func) (double d);

	};

	template <class T> 
	float Bisection<T>::findRoot(float startVal, float endVal, float tolerance, int iterateCount){

		if ((*_callerObj.*_func)(startVal)*(*_callerObj.*_func)(endVal)>0)
			throw "Invalid startVal or endVal!";
		if ((*_callerObj.*_func)(startVal)==0)
			return startVal;
		if ((*_callerObj.*_func)(endVal)==0)
			return endVal;

		float midVal;
		float y;
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