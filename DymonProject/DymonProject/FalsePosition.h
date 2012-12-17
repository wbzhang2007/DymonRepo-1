//created by Hu Kun 17 Dec

#ifndef FALSEPOSITION_H
#define FALSEPOSITION_H
#include "AbstractNumerical.h"

namespace utilities{
	class FalsePosition: public AbstractNumerical{
		
	public:
		
		FalsePosition(targetFuncT* func):AbstractNumerical(func){};

		static double findRoot(double (*funcd)(double), double x1, double x2, float xacc, int iterateCount);
	
	private:
		
	};
}
#endif