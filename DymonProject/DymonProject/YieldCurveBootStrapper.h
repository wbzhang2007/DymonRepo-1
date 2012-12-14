//created by Wang Jianwei on 01 Dec 2012
#ifndef YIELDCURVEBOOTSTRAPPER_H
#define YIELDCURVEBOOTSTRAPPER_H
#include <string>
#include "AbstractBootStrapper.h"

namespace utilities {
	class YieldCurveBootStrapper: public AbstractBootStrapper{
		
	public:
		
		typedef tuple<date, double> point;

		typedef double (*targetFuncT) (double d);

		YieldCurveBootStrapper(point startPoint, date endDate, double targetVal, AbstractInterpolator::interpolAlgo interpolAlgo,
		AbstractNumerical::NumericAlgo numericAlgo):AbstractBootStrapper(startPoint, endDate, targetVal, interpolAlgo, numericAlgo){};
				
		AbstractInterpolator* bootStrap();
	
		double numericalFunc(double xVal);
	};
}
#endif