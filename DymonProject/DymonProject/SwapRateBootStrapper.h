//created by Wang Jianwei on 01 Dec 2012
#ifndef SWAPRATEBOOTSTRAPPER_H
#define SWAPRATEBOOTSTRAPPER_H
#include <string>
#include "AbstractBootStrapper.h"
#include "cashflowLeg.h"

using namespace instruments;

namespace utilities {
	class SwapRateBootStrapper: public AbstractBootStrapper{
		
	public:
		
		typedef tuple<date, double> point;

		typedef double (*targetFuncT) (double d);

		SwapRateBootStrapper(point startPoint, date endDate, cashflowLeg* cashflows, AbstractInterpolator::interpolAlgo interpolAlgo,
		AbstractNumerical::NumericAlgo numericAlgo):AbstractBootStrapper(startPoint, endDate, interpolAlgo, numericAlgo){
			_cashflows = cashflows;
		}
				
		AbstractInterpolator* bootStrap();
	
		double numericalFunc(double xVal);

	private:

		cashflowLeg* _cashflows;
	};
}
#endif