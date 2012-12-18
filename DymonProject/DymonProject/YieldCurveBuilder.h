//created by Wang Jianwei on 01 Dec 2012
//Added cashflowleg creating - Kun
#ifndef YIELDCURVEBUILDER_H
#define YIELDCURVEBUILDER_H
#include "AbstractCurve.h"
#include "YieldCurve.h"
#include "AbstractBuilder.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include <vector>

using namespace instruments;

namespace utilities{
	class YieldCurveBuilder: public AbstractBuilder{
		
	public:
		
		YieldCurveBuilder():AbstractBuilder(){}

		void init(Configuration* cfg);

		YieldCurve* build();

	private:

		enums::CurrencyEnum _currencyName;
		enums::DayCountEnum _dayCountCashConvention;
		enums::DayCountEnum _dayCountSwapConvention;
		enums::DayRollEnum _dayRollConvention;
		int _floatFreqency;
		int _fixFreqency;
		int _timeLineBuildDirection;
		bool _rollAccuralDates;
		enums::interpolAlgo _interpolAlgo;
		enums::NumericAlgo _numericalAlgo;
	};
}
#endif