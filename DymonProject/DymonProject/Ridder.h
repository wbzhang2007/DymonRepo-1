//created by Hu Kun 17 Dec

#ifndef RIDDER_H
#define RIDDER_H
#include "AbstractNumerical.h"

namespace utilities{
	class Ridder: public AbstractNumerical{
		
	public:
		
		Ridder(targetFuncT* func):AbstractNumerical(func){};

		static double findRoot(double (*func)(double), double x1, double x2, float xacc, int iterateCount);
	
	private:
		
	};
}
#endif