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

		void init(Configuration* cfg);

		DepositRateBootStrapper(point startPoint, date endDate, double depositRate, vector<date>* timeLine, enums::interpolAlgo interpolAlgo,
			enums::NumericAlgo numericAlgo, enums::DayCountEnum dayCount):AbstractBootStrapper(startPoint, endDate, interpolAlgo, numericAlgo){
			_depositRate = depositRate;
			_timeLine = *timeLine;
			_dayCount = dayCount;
		};
				
		AbstractInterpolator* bootStrap();

		double numericalFunc(double x);

	private:

		double _depositRate;
		vector<date> _timeLine;
		enums::DayCountEnum _dayCount;

	};
}
#endif