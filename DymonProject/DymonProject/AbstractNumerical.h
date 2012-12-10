//created by Wang Jianwei on 01 Dec 2012
#ifndef AbstractNumerical_H
#define AbstractNumerical_H
#include <string>
#include "AbstractInterpolation.h"

using namespace utilities;

namespace AbstractNumerical{
	{
	public:
		double findRoot(double startVal, double endVal, double tolerance, int iterations);
		 
	private:
		AbstractInterpolation interpolator;
	};
}
#endif