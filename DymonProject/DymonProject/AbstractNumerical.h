//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTNUMERICAL_H
#define ABSTRACTNUMERICAL_H

namespace utilities{
	class AbstractNumerical{

	public:
		
		enum NumericAlgo {BISECTION, NEWTON};

		typedef int (*targetFuncT) (double d);

		AbstractNumerical(targetFuncT* func){};

		virtual double findRoot(targetFuncT func, double startVal, double endVal, double tolerance, int iterateCount);

	private:

		targetFuncT func;
	};
}
#endif