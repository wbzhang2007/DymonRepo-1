//created by Wang Jianwei on 01 Dec 2012
#include <iostream>

using namespace std;


#ifndef ABSTRACTNUMERICAL_H
#define ABSTRACTNUMERICAL_H


namespace utilities{
	class AbstractNumerical{

	public:
		
		enum NumericAlgo {BISECTION, NEWTON};

		typedef double (*targetFuncT) (double d);

		AbstractNumerical(targetFuncT* func){};

		virtual double findRoot(double startVal, double endVal, double tolerance, int iterateCount){return 0;}

	protected:

		targetFuncT _func;

		
	};
}
#endif