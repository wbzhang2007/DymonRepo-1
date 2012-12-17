//created by Wang Jianwei on 01 Dec 2012
#ifndef DEPOSITRATEBOOTSTRAPPER_H
#define DEPOSITRATEBOOTSTRAPPER_H
#include <string>
#include "AbstractBootStrapper.h"
#include "Enums.h"

namespace utilities {
	class DepositRateBootStrapper: public AbstractBootStrapper{
		
	public:
		
		typedef tuple<date, double> point;

		DepositRateBootStrapper(point startPoint, date endDate, double depositRate, vector<date>* timeLine, AbstractInterpolator::interpolAlgo interpolAlgo,
		enums::NumericAlgo numericAlgo):AbstractBootStrapper(startPoint, endDate, interpolAlgo, numericAlgo){
			_depositRate = depositRate;
			_timeLine = *timeLine;
		};
				
		AbstractInterpolator* bootStrap();

	private:

		double _depositRate;
		vector<date> _timeLine;
		enums::DayCountEnum _dayCount;

	};
}
#endif