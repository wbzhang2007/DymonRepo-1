
//created by Hu Kun 17 Dec

#ifndef SECANT_H
#define SECANT_H
#include "AbstractNumerical.h"

namespace utilities{
	class Secant: public AbstractNumerical{
		
	public:
		
		Secant(targetFuncT* func):AbstractNumerical(func){};

		static double findRoot(double (*func)(double), double x1, double x2, float xacc, int iterateCount);
	
	private:
		
	};
}
#endif