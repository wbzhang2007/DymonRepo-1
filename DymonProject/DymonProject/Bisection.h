//created by Wang Jianwei on 1 Dec 2012
#ifndef BISECTION_H
#define BISECTION_H
#include "AbstractNumerical.h"

namespace utilities{
	class Bisection: public AbstractNumerical{
		
	public:
		
		Bisection(targetFuncT* func):AbstractNumerical(func){};

		double findRoot(targetFuncT func, double startVal, double endVal, double tolerance, int iterateCount);
	};
}
#endif