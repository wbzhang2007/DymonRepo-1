//created by Wang Jianwei on 1 Dec 2012
#ifndef NEWTON_H
#define NEWTON_H
#include "AbstractNumerical.h"

namespace utilities{
	class Newton: public AbstractNumerical{
		
	public:
		
		Newton(targetFuncT* func):AbstractNumerical(func){};

		double findRoot(targetFuncT func, double startVal, double endVal, double tolerance, int iterateCount);
	};
}
#endif