//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTNUMERICAL_H
#define ABSTRACTNUMERICAL_H

namespace utilities{
	class AbstractNumerical{
		
	enum NumericAlgo {BISECTION,CUBICSPLINE};

	public:

		AbstractNumerical();

		virtual double findRoot(double startVal, double endVal, double tolerance, int iterateCount, NumericAlgo algo);

		double findRoot(double startVal, double increment, double tolerance);

	private:


	}
}
#endif