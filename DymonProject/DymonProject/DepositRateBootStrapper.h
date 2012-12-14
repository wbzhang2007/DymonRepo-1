//created by Wang Jianwei on 01 Dec 2012
#ifndef DEPOSITRATEBOOTSTRAPPER_H
#define DEPOSITRATEBOOTSTRAPPER_H
#include <string>
#include "AbstractBootStrapper.h"

namespace utilities {
	class DepositRateBootStrapper: public AbstractBootStrapper{
		
	public:
		
		typedef tuple<date, double> point;

		DepositRateBootStrapper(point startPoint, date endDate, AbstractInterpolator::interpolAlgo interpolAlgo,
		AbstractNumerical::NumericAlgo numericAlgo):AbstractBootStrapper(startPoint, endDate, interpolAlgo, numericAlgo){};
				
		AbstractInterpolator* bootStrap();
	};
}
#endif